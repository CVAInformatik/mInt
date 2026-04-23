/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

#include "mInt.h"
#include "mInt_lib.h"
#include "mInt_rand.h"
#include "MontmInt.h"
#include "MontmInt_lib.h"

/*
      result either 0 : the argument is probably a prime
            -1 : the argument is a composite, 
                 but we failed to find a factor within the iteration limit
            a mIntType > 0, a factor in the argument ( not necessarily the smallest factor )     
            
     the default iteration limit (1.000.000) may be too high for a quick small factor 
     check or too small for e.g. finding a factor in the seventh Fermat number F7 ((2^(2^7)+ 1)
     ( a limit around 6.000.000.000 should be enough, though).
            
*/

//DELTA controls how often we run the GCD
#define DELTA  17

mIntType MontPollardRho( mIntType & N , unsigned int IterationLimit )
{
	mIntType res;
	//std::cout<< std::endl << "MontPollardRho: " << iToA(N) << std::endl;
	if( MillerRabin( N, 29)){
		res = 0; 
		return res ;
	}
  return _MontPollardRho( N, IterationLimit);
}


mIntType _MontPollardRho( mIntType & N , unsigned int IterationLimit )
{
	mIntType res;
  int counter ;
  
	mIntType seed(1);
  MontmIntType nk1(N);
  MontmIntType nk2(nk1);
	MontmIntType one(nk1); 
	one.frommInt(seed);
  MontmIntType nkdiff(nk1);
  nk1.frommInt(seed);
  nk2 = nk1 ;
	for(int i = 0; i < IterationLimit ; i++)	{
		 nk1 *= nk1;
		 nk1 += one; // NK1 = NK1^2 +1 ; NK2 = (NK2^2 + 1)^2 +1 
		 nk2 *= nk2; 
		 nk2 += one;
		 nk2 *= nk2;
		 nk2 += one;
		 nkdiff = nk2;
		 nkdiff -= nk1;
		 if( 0 == (++counter % DELTA))
		 	{
		 		counter = 0;
		 		mIntType diff = nkdiff.tomInt();
		 		mIntType b1 ;
		 		mIntType b2 ;
		 		//extendedGCD(diff, N, res, b1, b2);
		 		binGCD(diff, N, res);
  	 		if( res != 1 ) return res;
		 	  }
		 	}
	res = -1 ;
  return res ;

}

mIntType  MontPollardRho(const char *s, unsigned int IterationLimit )
{
	mIntType N;  N = aToI(s);
  return MontPollardRho( N, IterationLimit) ;
}

