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

#include <iostream>
#include <iomanip> 
//
// simpel conversion from int tested 
void Montgomery_test( mIntType & N)
{

	std::cout << "Montgomery_test " << iToA(N) << std::endl;
  MontmIntType nk1(N);
  
  mIntType M =  nk1.tomInt();
	std::cout << "MontPollardRho: " << iToA(nk1.tomInt()) << std::endl;
	if ( M != N )
				std::cout << "Error " << iToString(M) <<" " << iToString(N) << std::endl;
	return ;
}


void MontPollardRho_lib( mIntType & N)
{
	
	int counter = 0;
	std::cout<< std::endl << "MontPollardRho: " << iToA(N) << std::endl;
	mIntType res = MontPollardRho( N,800000000);
	if( res.Sign() == -1)
          std::cout << "*****Composite, but iteration limit reached **************************************" << std::endl;
  else if (res.Sign() == 0) 
          std::cout << "***** Probably a prime **************************************" << std::endl;
  else {
  	 		 std::cout << "*******************************************" << std::endl;
	   		 std::cout << "   N              = " << iToA(N) << std::endl;
	   		 std::cout << "   Divisor        = " << iToA(res) << std::endl;
	   		 mIntType q; q =N; q/= res;
	   		 std::cout << "   q = N/divisor  = " << iToA(q) << std::endl;
	   		 std::cout << "   q * divisor    = " << iToA(q * res) << std::endl;
  	 		 std::cout << "*******************************************" << std::endl;
	  }
  
}

void MontPollardRho_lib( const char *c)
{
	mIntType N ; N = aToI(c);
	MontPollardRho_lib(N) ;
}

void testMontgomery_lib()
{

  MontPollardRho_lib("649037107316853453566312041152511");//M109
  MontPollardRho_lib("2535301200456458802993406410751");//M101
  MontPollardRho_lib("803469022129495137770981046170581301261101496891396417650687");//M199
  MontPollardRho_lib("115792089237316195423570985008687907853269984665640564039457584007913129639937");//F8
  MontPollardRho_lib("340282366920938463463374607431768211457");//F7
  MontPollardRho_lib("13407807929942597099574024998205846127479365820592393377723561443721764"
                 "0300735469768018742981669034276900318581864860508537538828119465699464336"
	               "49006084097"); // F9	
	mIntType F10(1);
	F10 <<= 1024 ;
	F10 += 1;
	MontPollardRho_lib(F10);
	mIntType F11(1);
	F11 <<= 2048 ;
	F11 += 1;
	MontPollardRho_lib(F11);
	mIntType F12(1);
	F12 <<= 4096 ;
	F12 += 1;
	MontPollardRho_lib(F12);
	/* Nope, appears difficult
	mIntType F13(1);
	F13 <<= 8192 ;
	F13 += 1;
	MontPollardRho_lib(F13);
	*/
}

/* 
  basic test 
*/
void testMontgomery1()
{
#define APRIME  65537

  MontmIntType  t(APRIME);
  
  for(int i = 0; i < (APRIME+10); i++){
  	mIntType a(i);
  	mIntType b;
  	mIntType c(i % APRIME);
  	t.frommInt(a);
  	b = t.tomInt();
  	if ( c  != b)
  		std::cout << "error " << iToA(a) << " != "<< iToA(b) << std::endl;
  }
  
  MontmIntType  t1(APRIME);
  MontmIntType  t2(t1);
  MontmIntType  t3(t1);
  for(int i1 = 0; i1 < (APRIME+10); i1 += 3){
  	for(int i2 = i1+1; i2 < (APRIME+10); i2+=7){
  	mIntType a(i1);
  	mIntType b(i2);
  	mIntType c( (i1+i2)% APRIME );
  	t1.frommInt(a);
  	t2.frommInt(b);
  	t3.frommInt(c);
  	t1 += t2;
  	std::cout << " "  << i1 << " " << i2 << std::endl;
  	if ( t3  != t1)
  		std::cout << "error " << iToA(c) << " != "<< iToA(b) << std::endl;
  		}
  }

  MontmIntType  t11(APRIME);
  MontmIntType  t22(t11);
  MontmIntType  t33(t11);
  for(int i1 = 0; i1 < (APRIME+10); i1 += 3){
  	for(int i2 = i1+1; i2 < (APRIME+10); i2+=7){
  	mIntType a(i1);
  	mIntType b(i2);
  	unsigned long long ct = (i1*i2)% APRIME;
  	mIntType c( ct );
  	t11.frommInt(a);
  	t22.frommInt(b);
  	t33.frommInt(c);
  	t11 *= t22;
  	std::cout << " "  << ct << " "  << iToA(t11) << std::endl;
  	if ( t33  != t11)
  		std::cout << "error " << iToA(c) << " != "<< iToA(b) << std::endl;
  		}
  }
 
}



/*
    Make a lot of randum mInts, if not prime try to factor them using MontPollardRho2:
*/
void testMontgomery3_lib()
{
    Rand_mIntType Rands;
    
#define COUNT2 1000

  
    for (int i = 0; i < COUNT2; i++) {
      	  mIntType pc = Rands.rand(330);
        	if (!pc.isOdd()) pc += 1;
					mIntType res = MontPollardRho( pc,100000);
					if( res.Sign() == -1){
          		std::cout << "*****Composite, but iteration limit reached **************************************" << std::endl;
	   		 			std::cout << "   N              = " << iToA(pc) << std::endl;
  	 				 	std::cout << "*******************************************" << std::endl;
          }
  				else if (res.Sign() == 0) {
          		std::cout << "***** Probably a prime **************************************" << std::endl;
	   		 			std::cout << "   N              = " << iToA(pc) << std::endl;
  	 				 	std::cout << "*******************************************" << std::endl;
          }
				  else {
  	 				 	std::cout << "*******************************************" << std::endl;
	   		 			std::cout << "   N              = " << iToA(pc) << std::endl;
	   		 			std::cout << "   Divisor        = " << iToA(res) << std::endl;
	   		 			mIntType q; q =pc; q/= res;
	   		 			std::cout << "   q = N/divisor  = " << iToA(q) << std::endl;
	   		 			std::cout << "   q * divisor    = " << iToA(q * res) << std::endl;
  	 		 			std::cout << "*******************************************" << std::endl;
	  			}
        		
    }        
}


int main(int argc, char **argv){

   //testMR2();
	 //testMontgomery();
	 //testMontgomery2();
	 //testMontgomery3_lib();
	 testMontgomery_lib();
	 return 0 ;
}