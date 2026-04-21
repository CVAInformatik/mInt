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

void MontPollardRho( mIntType & N)
{
	
	int counter = 0;
	std::cout<< std::endl << "MontPollardRho: " << iToA(N) << std::endl;
	if( MillerRabin( N, 29)){
		std::cout << "MontPollardRho: probably a prime " << iToA(N) << std::endl;
	}

#define LIM1 2000000000	

	mIntType seed(1);
  MontmIntType nk1(N);
  MontmIntType nk2(nk1);
	MontmIntType one(nk1); 
	one.frommInt(seed);
  MontmIntType nkdiff(nk1);
  nk1.frommInt(seed);
  nk2 = nk1 ;
	for(int i = 0; i < LIM1 ; i++)	{
		 nk1 *= nk1;
		 nk1 += one;
		 nk2 *= nk2; 
		 nk2 += one;
		 nk2 *= nk2; //modmult(nk2,nk2, N);
		 nk2 += one;
		 nkdiff = nk2;
		 nkdiff -= nk1;
		 if( 0 == (++counter % 8))
		 	{
		 		counter = 0;
		 		mIntType diff = nkdiff.tomInt();
		 		mIntType g ;
		 		mIntType b1 ;
		 		mIntType b2 ;
		 		extendedGCD(diff, N, g, b1, b2);
  	 		if( g != 1 ){
  	 		 std::cout << "*******************************************" << std::endl;
	   		 std::cout << "   N              = " << iToA(N) << std::endl;
	   		 std::cout << "   Divisor        = " << iToA(g) << std::endl;
	   		 mIntType q; q =N; q/=g;
	   		 std::cout << "   q = N/divisor  = " << iToA(q) << std::endl;
	   		 std::cout << "   q * divisor    = " << iToA(q * g) << std::endl;
  	 		 std::cout << "*******************************************" << std::endl;
	   		return ;
		 	  }
		 	}
	}

}

void MontPollardRho(const char *s) 
{
	mIntType N;  N = aToI(s);
  MontPollardRho( N) ;
}

void testMontgomery2()
{

  //MontPollardRho("649037107316853453566312041152511");//M109
  //MontPollardRho("2535301200456458802993406410751");//M101
  //MontPollardRho("803469022129495137770981046170581301261101496891396417650687");//M199
  //MontPollardRho("115792089237316195423570985008687907853269984665640564039457584007913129639937");//F8
  //MontPollardRho("340282366920938463463374607431768211457");//F7
  //MontPollardRho("13407807929942597099574024998205846127479365820592393377723561443721764"
  //"0300735469768018742981669034276900318581864860508537538828119465699464336"
	//"49006084097"); // F9	
	mIntType F10(1);
	F10 <<= 1024 ;
	F10 += 1;
	MontPollardRho(F10);
	mIntType F11(1);
	F11 <<= 2048 ;
	F11 += 1;
	MontPollardRho(F11);
	mIntType F12(1);
	F12 <<= 4096 ;
	F12 += 1;
	MontPollardRho(F12);
	/* Nope, appears difficult
	mIntType F13(1);
	F13 <<= 8192 ;
	F13 += 1;
	MontPollardRho(F13);
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
void testMontgomery3()
{
    Rand_mIntType Rands;
    mIntType prime; prime = aToI("26959946667150639794667015087019630673557916260026308143510066298881");
    mIntType prime1; prime1 = aToI("5127821565631733");
   	mIntType prime2; prime2 = aToI("2147483647");

#define COUNT2 100

    mIntType seed(prime1);
    
  	std::string s = iToString(seed);
    int w = s.length();
    std::cout << std::endl<< "seed: "<< std::setw(w) << s <<" (" << std::setw(5) << w <<" digits" <<" ) " <<  std::endl << std::endl;
    for (int i = 0; i < COUNT2; i++) {
      	  mIntType pc = Rands.rand(seed);
        	if (!pc.isOdd()) pc += 1;
     	    if (MillerRabin(pc, 30))
        			std::cout << std::setw(w+6) << s << " is probably prime " << std::endl;    			
    			else 
    				 MontPollardRho( pc);			    
    }        
}

void testMontgomery()
{
    mIntType prime; prime = aToI("26959946667150639794667015087019630673557916260026308143510066298881");

    mIntType prime1; prime1 = aToI("5127821565631733");

   	mIntType prime2; prime2 = aToI("2147483647");
#define WIDTH 75
    int np = 0, p = 0;

    Rand_mIntType Rands;


#define COUNT 1000

    np = 0;
    p = 0;

    mIntType seed(prime1);
    
  	  std::string s = iToString(seed);
    	int w = s.length();
    	std::cout << std::endl<< "seed: "<< std::setw(w) << s <<" (" << std::setw(5) << w <<" digits" <<" ) " <<  std::endl << std::endl;
    	for (int i = 0; i < COUNT; i++) {
      	  mIntType pc = Rands.rand(seed);
        	if (!pc.isOdd()) pc += 1;
     	    if (MillerRabin(pc, 30)) {
        			std::cout << std::setw(w+6) << s << " is probably prime " << std::endl;
    			}
    			else {
    				 Montgomery_test( pc);
			    };
    	}        
}



int main(int argc, char **argv){

   //testMR2();
	 //testMontgomery();
	 testMontgomery2();
	 return 0 ;
}