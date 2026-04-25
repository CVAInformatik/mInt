#pragma once
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


void REDC(  const mIntType &R, const mIntType &N, const mIntType &Ninv,mIntType &a);


class MontmIntType
{
public:
	
	MontmIntType( const mIntType &_N)
	{
		 val = 0 ;
		 N = _N;
		 R =  1; Rdigits = 1;
  	 while ( N > R) { 
   	 	R.mulModulus();
  	 	Rdigits++;
  	 	}
		 mIntType gcd ;

		 extendedGCD(R, N, gcd, Rinv, Ninv);
		 /*
 		std::cout << "- montType()  : N    " << iToA(N) << std::endl;
		std::cout << "- montType()  : R    " << iToA(R) << std::endl;
		std::cout << "- montType()  : Rinv " << iToA(Rinv) << std::endl;
		std::cout << "- montType()  : Ninv " << iToA(Ninv) << std::endl;
      */
		 
		 if (gcd != 1) {
			 	std::cout << "MontmIntType: R and N not prime !! R: " 
		       <<  iToA(R) << " N: " << iToA(N) << std::endl;		 		 
		    return;
		 }

    // mInts GCD returns Bezout coefficents(== Rinv, Ninv)  so R x Rinv + N x Ninv = GCD, 
    // ( R and N have different signs)
    // but Peter Montgomery uses the convention 
    //   Rinv > 0, Ninv > 0,  R x Rinv - N x Ninv = GCD 
    //   If Rinv is negative, we will have to adjust for this
    //   R x Rinv + N x Ninv == 1 ==>                   ( we add zero )
    //   R x Rinv + 0 +  N x Ninv == 1 ==>              ( in the form of (R x N - R x N) = 0
    //   R x Rinv + (R x N - R x N) +   N x Ninv == 1 > == > ( and rearrange )
    //   R x (Rinv + N) + N x ( Ninv - R) == 1         ( until Rinv > 0 )
		while (( Rinv.Sign() == -1) ) {
			    mIntType rq;
			    rq = Rinv; rq.ChangeSign(); rq/= N;
			    if (rq.Sign() == 0) rq = 1;
			 	  Rinv += ( N* rq) ;
			 	  Ninv -= ( R* rq) ;
  	}
  	// Rinv is here  positive and Ninv negative, so to  follow Montgomery
    Ninv.ChangeSign();
	} 

	MontmIntType( const MontmIntType &m){ 		 
		 val = m.val;
		 N = m.N; 
		 R = m.R;
		 Rinv = m.Rinv;
		 Rdigits = m.Rdigits;
		 Ninv = m.Ninv;
		 };	
		 
	~MontmIntType() {} ;

	MontmIntType& operator=(MontmIntType& b){ 
						if (&b == this) return *this;
		  			else {
		           val = b.val ; 
		           N = b.N;
		           R = b.R;
		           Rdigits = b.Rdigits;
		           Ninv = b.Ninv;
		           Rinv = b.Rinv;
		           return *this;};
					}
	MontmIntType& operator+=( const MontmIntType& b){ 
								val += b.val ;
		            if(N == val) val = 0;
		            if(N < val) val -= N;
		            return *this;
		       }
		                                        
	MontmIntType& operator-=( const MontmIntType& b){ 
						val -= b.val ;
		        if(val.Sign() == -1) val += N ;
		        return *this;
		       }
		            		                                        
	MontmIntType& operator*=( const MontmIntType& b){ 
						val *= b.val ; 
						REDC(R, N, Ninv, val);																					  
						return *this;
					}
																						
	bool  operator==( 	const MontmIntType& b){
		  			return (val == b.val) && (R ==b.R) && (N == b.N);
					}																				
	
	bool  operator!=( 	const MontmIntType& b){	return !( *this==b); }																				
	
	mIntType tomInt() const ;
 	MontmIntType   &frommInt(const mIntType &a);
 	
	
private:
	
	mIntType val;
	mIntType N ;
	mIntType R ;
	unsigned int Rdigits;
	mIntType Ninv ;
	mIntType Rinv ;
};


std::string  iToA(const MontmIntType &a ) ; 