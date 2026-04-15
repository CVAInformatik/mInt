/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

#include <iostream>
#include "mInt.h"
#include "mInt_lib.h"
#include "mInt_rand.h"

#ifdef MERSENNE		
void  Mersenne(unsigned int _N,  mIntType &a )
{
	
	  unsigned int N = _N;
	  a = 1 ;
	  while( N >20){
	  	 N -= 20;
	  	 a *= (1024*1024);
	  }
	  while (N--) a <<= 1 ; 
	  a -= 1;
}
#endif


#ifdef GCD
void _GCD(const mIntType &a, const mIntType &b, mIntType &gcd)
{
	  if(a.Sign()== 0) { gcd =  0; return ;}
	  if(b.Sign()== 0) { gcd =  0; return ;}
	  
	  unsigned int shift = 0;
	  mIntType _ac(a);
	  mIntType _bc(b);
	  
	  while ( !_ac.isOdd() && !_bc.isOdd()){
	  	 _ac >>= 1;
	  	 _bc >>= 1;
	  	 shift++;
	  }

	  while (!_ac.isOdd()) _ac >>= 1;
	  
    while (_bc.Sign() > 0) {
	 			 while (!_bc.isOdd()) _bc >>= 1;	
				 if( _ac < _bc ) {
	 			 	mIntType swap = _ac ;
	 			 	_ac = _bc;
	 			 	_bc = swap;
	 			 }
	 			 _bc -= _ac;
	 			 _bc >>= 1 ; 
		}
		_ac <<= shift ;
		gcd = mIntType(_ac);
}
#endif
#if 1
/*
function extended_gcd(a, b)
    (old_r, r) := (a, b)
    (old_s, s) := (1, 0)
    (old_t, t) := (0, 1)
    
    while r ? 0 do
        quotient := old_r div r
        (old_r, r) := (r, old_r - quotient × r)
        (old_s, s) := (s, old_s - quotient × s)
        (old_t, t) := (t, old_t - quotient × t)
    
    output "Bézout coefficients:", (old_s, old_t)
    output "greatest common divisor:", old_r
    output "quotients by the gcd:", (t, s)
*/

void extendedGCD(const mIntType &a, const mIntType &b, mIntType &gcd, mIntType &am, mIntType &bm  )
{
	mIntType old_r(a);
	mIntType r(b);
	mIntType old_s((long long) 1);
	mIntType s((long long) 0);
	mIntType old_t((long long) 0);
	mIntType t((long long) 1);
	
	while(!r.Sign() == 0){
		 mIntType quotient ;
		 mIntType rem;
		 DivRem( old_r, r, quotient, rem);
		 { // (old_r, r) := (r, old_r - quotient × r)
		 	  mIntType temp_oldr(old_r);
		 	  old_r = r;
		 	  r *= quotient ;
		 	  r.ChangeSign();
		 	  r += temp_oldr;		 	  
		 }
		 { // (old_s, s) := (s, old_s - quotient × s)
		 	 mIntType temp_olds(old_s);
		 	 old_s = s;
		 	 s *= quotient;
		 	 s.ChangeSign();
		 	 s +=  temp_olds;
		 }
		 { //  (old_t, t) := (t, old_t - quotient × t)
		 	  mIntType temp_oldt(old_t);
		 	  old_t = t;
		 	  t *= quotient;
		 	  t.ChangeSign();
		 	  t += temp_oldt;
		 }		
	}
  gcd = old_r;
	am =  old_s;
	bm =  old_t;	
}

#endif

#define JACOBI
#ifdef JACOBI
//
//  From Wikipedia, with a small change
//
int Jacobi(const mIntType& _a, const mIntType& _n)
{
	 mIntType a(_a);
	 mIntType n(_n);
	
	 if( !n.isOdd()) { printf("Jacobi n must be odd\n"); return 0; }
	 if( n <= 0) 	{    printf("Jacobi n must positive\n"); return 0; }
	 	
	 while ( a < 0 ) a += n;
	 
	 int t = 0;
	 
	 while (a != 0){
	 	while ((a.LSD() & 3) == 0) a >>= 2;
	 	if((a.LSD() & 1) == 0){
	 		 t ^= n.LSD() & 6 ;
	 		 a >>= 1 ;
	 	}
	 	t ^= a.LSD() & n.LSD() & 2 ;
	 	mIntType r(n);
	 	r %= a;
	 	n = a ;
	 	a = r ;
	 }
	 if( n != 1 ) return 0;
	 switch (t)
	 {
	 	  case 2: case 3:
	 	  case 4: case 5:	return -1; break;
	 	  default: return 1 ;
	 }
}
#endif

#ifdef MODMULTEXP

// Compute (a*b) % mod
mIntType modmult(const mIntType &_a, const mIntType &_b, const mIntType &mod) {  
    mIntType result;
    mIntType a = _a;
    mIntType b = _b;
    while (b.Sign()) {
        if (b.isOdd()) {
            result += a;
            result %= mod ;
        }
        a = a + a;
        a %= mod;
        b >>= 1;
    }
    return result;
}

// Compute a^b % mod
mIntType modpow(const mIntType& _a, const mIntType& _b, const mIntType& mod) { 
    mIntType result;
    mIntType  a = _a;
    mIntType  b = _b;
    mIntType t;
    
    result = 1 ;
    while (b.Sign()) {
        if (b.isOdd()) {
            t = modmult(result, a, mod);
            result = t;
        }
        a = modmult(a, a, mod);
        b >>= 1;
    }

    return result;
}

#endif


#ifdef MILLERRABIN
bool MillerRabin(const mIntType &number, int witnesses)
{
    mIntType m = number;

    if (!m.isOdd()) {
        std::cout << "argument must be odd " << std::endl;
        return false;
    }
    else {

        Rand_mIntType Rands;

        mIntType d = m;  
        int s = 0;
 
        d -= 1;
        while (d.Sign() && !d.isOdd()) {
            d >>= 1;
            s++;
        }

        for (size_t ix = 0; ix < witnesses; ix++)
        {
            mIntType a = Rands.rand(number);
            a += 2;

            //std::cout << "a: " << a.ToString() << std::endl;
            mIntType x = modpow(a, d, m);

            for (int i = 0; i < s; i++) {
               mIntType y = modmult(x, x, m);
               mIntType t = m;
               t -= x;
               if ((y == 1) && ( x != 1) && (t!=1)) {
                   std::cout << "mr fail at " << ix << " ";
                    return false;  
                }
                x = y;
            }
            if (x != 1 ) {
                std::cout << "mr fail at " << ix << " ";
                return false;
            }
        }
    }
    return true;
}

#endif


#ifdef TONELLISHANKS
bool  TonelliShanks(const mIntType & n, const mIntType& p, mIntType& res) {

    mIntType Res; 
		if (Jacobi(n, p) != 1) {
			Res = 0;
			res = Res;
			return false;
		}

	// Factor out powers of 2 from p - 1
	mIntType q = p; q -= 1;
	int s = 0;
	while (!q.isOdd()) {
		if (q.Sign() == 0) {
            res = 0;
			std::cout << "not a square " << std::endl;
			return false;
		}
		q >>= 1;
		s++;
	}

	// Find a non-square z such as ( z | p ) = -1
	mIntType z = 2;
	Rand_mIntType Rands;

	do {
		z = Rands.rand(p);
	} while (Jacobi(z, p) != -1);

	mIntType c = modpow(z, q, p);
	//std::cout << " z: " << iToString(z) << std::endl;
	//std::cout << " q: " << iToString(q) << std::endl;
		mIntType p1 = p;
	//std::cout << " p: " << iToString(p1) << std::endl;
	//std::cout << " c: " << iToString(c) << std::endl;
		mIntType  t = modpow(n, q, p);
		mIntType  m = s;
		mIntType  m_1 = m;
		mIntType  result = modpow(n, (q + 1) >>= 1, p);

	//std::cout << " c: " << iToString(c) << std::endl;
	//std::cout << " t: " << iToString(t) << std::endl;
	//std::cout << " m: " << iToString(m) << std::endl;
	//std::cout << " R: " << iToString(R) << std::endl;

loop:
	if (t.Sign() == 0) {
		res = 0;
		std::cout << "Root is 0" << std::endl;
		return false;
	}
	if (t == 1) {
        res = result;
		std::cout << "Root is " << iToString(result) << std::endl;
		return true;
	}
	int  i = 0;
		mIntType t1 = t;
	do {
		i++;
		t1 = modmult(t1, t1, p);
	} while (t1 != 1);



		mIntType temp1 = m;
	temp1 -= 1;
	temp1 -= i;

		mIntType temp2;

	temp2 = modpow(2, temp1, p);

		mIntType  b = modpow(c, temp2, p);
	c = modmult(b, b, p);
	t = modmult(t, c, p);
	m = i;
	result = modmult(result, b, p);
	//std::cout << " c: " << iToString(c) << std::endl;
	//std::cout << " t: " << iToString(t) << std::endl;
	//std::cout << " R: " << iToString(result) << std::endl;

	goto loop;
	return  true;
}


bool  CheckedTonelliShanks(const mIntType& n, const mIntType& p, mIntType& res) {

    // is p a prime ??
    if (MillerRabin(p, 30)) 
    	return TonelliShanks(n, p, res);
    else 
    	return false;
}

#endif

#ifdef EXPONENTIATION
mIntType exponentiation(int  a, int exp)
{
    mIntType res;

    unsigned int  mask = exp >> 1;
    if (exp == 0) 
        res = 1;
    else if (mask == 0) // exponent == 1
            res = a;
    else {
        mask |= mask >> 1;
        mask |= mask >> 2;
        mask |= mask >> 4;
        mask |= mask >> 8;
        mask |= mask >> 16;
        mask++;  // mask is now a single 1 at the postion of the leftmost 1 in exp
        mask = mask >> 1;
        res = a;
        do {
            res *= res;
            if (exp & mask)
                res *= a;
            mask = mask >> 1;
        } while (mask);
    }
    return res;
}
#endif
