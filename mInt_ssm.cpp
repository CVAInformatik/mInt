/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

/*
   Schoenhage-Strassen Multiplication
   
*/

#include "mInt.h"
#include "mInt_ssm.h"


#include "FFTBase.h"
#include "simpleRadix2IOIPFFTindex.h"
#include "simple32NIOIPFFT.h"
#include "FFTClass.h"

#ifdef DECIMAL
#define RMOD3 1000
#else
#define RMOD3 1024
#endif

FFTClass * mIntType::fft{0};
FFTType * mIntType::re{0} ;
FFTType * mIntType::im{0} ;
size_t  mIntType::SSMallocation{0};


static void LoadFFT(const std::vector<baseType>& A, double* Buffer)
{
	int carry = 0;
	int FFTIndex = 0;
	for (size_t ix = 0; ix < A.size(); ix++) {
		int temp = (A[ix] >= 0) ? A[ix] : -A[ix];   // temp is  radix 10^9 
		for (int i = 0; i < 3; i++) {
			int tmp = (temp % RMOD3);// tmp is  radix RMOD3
			temp = temp / RMOD3;
			tmp = tmp + carry; carry = 0;
			if (tmp >=(RMOD3 / 2)) {  // tmp is 'balanced' radix RMOD3
				tmp = tmp - RMOD3;
				carry++;
			}

			Buffer[FFTIndex++] = (double)tmp;
		}
	}
	if (carry)
		Buffer[FFTIndex] = 1.0;
}


static void Carry(int64_t size, FFTType *Buffer)
{
	int64_t carry = 0;  // these must be 64 bit integers
	int64_t tmp = 0;

	/* conversion from 'balanced' Radix 2^10 double  to unbalanced Radix 2^10 double */
	for (size_t i = 0; i < size; i++)
	{
		tmp = (int64_t)std::round(Buffer[i]);

		tmp += carry; carry = 0;
		while (tmp < (-1 * (RMOD3 / 2))) { tmp += RMOD3; carry--; }
		while (tmp >= (RMOD3 / 2)) { tmp -= RMOD3; carry++; }
		Buffer[i] = (double)tmp;
	}
	carry = 0;
	/* carry we are still in Radix RMOD3 double*/
	for (size_t i = 0; i < size; i++)
	{
		tmp = (int64_t)std::round(Buffer[i]);
		tmp += carry;  carry = 0;
		if (tmp < 0) { tmp += RMOD3; carry--; }
		Buffer[i] = (double)tmp ;
	}

}

	//static FFTBufferType re, im ;


/*

		we convert each radix 2^30/10^9 digit to 3 Radix 2^10/10^3 digits
		put one of the factors in the real part, the other factor in the imaginary part.
		convert each radix 2^10/10^3 digit to 'balanced representation
	  (so they are in the range [-512..511]/[-512...511] in order to minimize noise.
		perform the FFT and untangle the two spectras and multiply them point by point
		perform the inverse FFT (which will give a pure real result, apart from some ignorable 
		noise in the complex part), handle interdigit carry for the 2^10/10^3 bit values.
		convert back to radix 2^30/10^9.
		we need a factor 6 larger FFT than the largets factorsize, 
		a factor 3 to handle the Radix 2^30/10^9 to Radix 2^10/10^3 conversion
		and a factor 2 to make a linear convolution from a circular one 	without overlap.
*/


#define DBG(N) do{ std::cout << " N " << N << std::endl;	 return;} while (0) 

//
// result is returned in a, so this is   a *= b  
//
void  SchStrMultiply(FFTClass  *fft, FFTType *re, FFTType *im, std::vector<baseType> & a, const std::vector<baseType> & b)
{
	
  if(fft == 0) return;
  if(re == 0) return;
  if(im == 0) return;
  	
  if( a.size() == 0) return ;
  if( b.size() == 0) { a.clear(); return; };

	//DBG(0) ;
  	
	int aSign = a.back() >= 0 ? 1 : -1;
	int bSign = b.back() >= 0 ? 1 : -1;

  /* sign noted for now, we will ignore the sign and multiply
     the numbers as positive numbers, then update the sign at 
     the end 
  */

	u32 max = a.size();
	if( max < b.size()) max = b.size() ;

// convenient to have a sligthly large buffer, 
// when we convert back	 to radix 30

#define SLACK 2
	u32 length = fft->FindLength ( max *6)	;

	fft->Length(length);
	
	u32 N = fft->Status();
	
	while (mIntType::SSMallocation < (N + SLACK))
	{
		mIntType::SSMallocation *= 2  ;
		std::cout << "Allocation 1" << mIntType::SSMallocation << std::endl;
		delete [] mIntType::re ;
		delete [] mIntType::im ;
		mIntType::re = new FFTType[mIntType::SSMallocation];
		mIntType::im = new FFTType[mIntType::SSMallocation];
		std::cout << "Allocation 2" << mIntType::SSMallocation << std::endl;
	}
	
	memset(re, 0, sizeof(FFTType) * (N+SLACK));
	memset(im, 0, sizeof(FFTType) * (N+SLACK));

	if( N){
		 
  	 LoadFFT(a, re);
		 LoadFFT(b, im);
	 
		 fft->ForwardFFT(re, im);


    /* 
    more space efficient, we work in-place 
    processing entry [i] and entry [N-i] simultaneous.
    */
		for (u32 i = 1; i < N/2; i++)
		{
			FFTType X01Real = re[i];
			FFTType X01Imag = im[i];
			FFTType X02Real = re[N - i];
			FFTType X02Imag = im[N - i];
			FFTType X1RealiN = (X01Real + X02Real) / 2.0;
			FFTType X1Imagi = (X01Imag - X02Imag) / 2.0;
			FFTType X1ImagN = -X1Imagi;//(X02Imag - X01Imag) / 2.0;
			FFTType X2Imagi = -1 * (X01Real - X02Real) / 2;
			FFTType X2ImagN = -X2Imagi ;;//-1 * (X02Real - X01Real) / 2;
			FFTType X2RealiN = (X01Imag + X02Imag) / 2;
			FFTType X3Reali = X1RealiN * X2RealiN - X1Imagi * X2Imagi;
			FFTType X3Imagi = X1RealiN * X2Imagi + X1Imagi * X2RealiN;
			FFTType X3RealN = X2RealiN * X1RealiN - X2ImagN * X1ImagN;
			FFTType X3ImagN = X2RealiN * X1ImagN + X2ImagN * X1RealiN;
			re[i] = X3Reali;
			im[i] = X3Imagi;
			re[N-i] = X3RealN;
			im[N-i] = X3ImagN;
		}
		re[0] *= im[0];
		im[0] 	= 0.0;
		re[N/2] *= im[N/2] ;
		im[N/2] = 0.0;

						
		fft->InverseFFT(re, im);

 

		Carry(N, re);

	  a.clear();
		
		for (int i = 0; i < N; i += 3)// can do this, thanks to SLACK
		{
			int t0 = (int) re[i];
			int t1 = RMOD3 * (int) re[i + 1];        // these values are 0 when we reach
			int t2 = RMOD3 * RMOD3 * (int) re[i + 2];// the end of buffer, due to
			a.push_back(t0 + t1 + t2);              // SLACK
		}

		while (a.size() && (a.back() == 0)) a.pop_back();


		
		if((aSign * bSign) < 0) /* negative result*/
		     for( int i = 0 ; i < a.size(); i++) a[i] = -a[i];				
  }

}
