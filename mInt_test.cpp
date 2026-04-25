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

#include <iostream>
#include <iomanip> 

void testShifts()
{
	
	mIntType x ;
	x = 0x3FFFFFFF;
	for( int i = 0; i < 200 ; i++){
			printf("\n iToString() shift %3d",i);
			std::cout << "  " << iToString(x) ;
			x <<= i ;
			std::cout << "  " << iToString(x)  << std::endl;
			x >>= i ;
			printf("\n iToA()      shift %3d",i);
			std::cout << "  " << iToA(x)  ;
			x <<= i ;
			std::cout << "  " << iToA(x)  << std::endl;
			x >>= i ;
	}
}

#ifdef ITOA
void testItoAtoI()
{
	
	 mIntType x ;
	 
	 x = aToI("0");  printf("%s\n", iToA(x));
	 x = 297193;  printf("%s\n", iToA(x));
	 x = aToI("297193");  printf("%s\n", iToA(x));
	 x = aToI("2971939296349239267359623956296539265");  printf("%s\n", iToA(x));
	 
	 x = aToI("107374182");  printf("%s\n", iToA(x));
	 x = aToI("10737418241");  printf("%s\n", iToA(x));
/**/
	 x = aToI("1073741821");  printf("%s\n", iToA(x));
/*	 x = aToI("1073741822");  printf("%s\n", iToA(x));
	 x = aToI("1073741823");  printf("%s\n", iToA(x));
	 x = aToI("1073741824");  printf("%s\n", iToA(x));
*/
}

#endif

#ifdef ITOSTRING
#ifdef MERSENNE 		
void testMersenne()
{
#if 1	
   mIntType x ;
   for( int i = 10 ; i < 200; i++){
  			Mersenne( i, x);// x.ChangeSign();
  			printf("\n testMersenne  %5d : ", i);
  			printf("%s \n",iToA(x));
  			std::cout << "iToString() "  << iToString(x) << std::endl;
 		}
#endif 		

#define MES(x) do {mIntType y; Mersenne(x,y); std::string s = iToString(y); std::cout \
	        <<std::endl<<" testMersenne "<< x << " " << s.length() << " "<< std::endl << s << std::endl ;} while (0)		
	        	
  	//		Mersenne( 2000, x); printf("\n testMersenne  %5d : ", 2000);	printf("%s \n",iToA(x));

    MES(2000);
    MES(5000);
    MES(10000);
    MES(15000);
		MES( 21701); 
		MES( 44497); 
    MES( 86243); 

}

#endif
#endif

#ifdef ATOI
void tc00(){
	 mIntType  a,b;

	  a = aToI("99999999");
	  printf("\n test case 00.1: a    %9s \n", iToA(a));
	  b = aToI("1");
	 	printf(" test case 00.1: b    %9s \n", iToA(b));
 		a += b ;
	 	printf(" test case 00.1: a+b  %9s \n", iToA(a));
	 
	  a = aToI("999999999");
	  printf("\n test case 00.2: a     %9s \n", iToA(a));
	  b = aToI("1");
	 	printf(" test case 00.2: b     %9s \n", iToA(b));
 		a += b ;
	 	printf(" test case 00.2: a+b  %9s \n", iToA(a));

	  a = aToI("9999999999");
	  printf("\n test case 00.3: a     %9s \n", iToA(a));
	  b = aToI("1");
	 	printf(" test case 00.3: b      %9s \n", iToA(b));
 		a += b ;
	 	printf(" test case 00.3: a+b  %9s \n", iToA(a));

	  a = aToI("99999999999");
	  printf("\n test case 00.4:  a    %9s \n", iToA(a));
	  b = aToI("1");
	 	printf(" test case 00.4: b       %9s \n", iToA(b)); 
 		a += b ;
	 	printf(" test case 00.4: a+b  %9s \n", iToA(a));
	  
}


void tc01(){
	 mIntType  a,b;

	  a = aToI("-99999999");
	  printf("\n test case 01.1: a    %9s \n", iToA(a));
	  b = aToI("-1");
	 	printf(" test case 01.1: b     %9s \n", iToA(b));
 		a += b ;
	 	printf(" test case 01.1: a+b  %9s \n", iToA(a));
	 
	  a = aToI("-999999999");
	  printf("\n test case 01.2: a     %9s \n", iToA(a));
	  b = aToI("-1");
	 	printf(" test case 01.2: b      %9s \n", iToA(b));
 		a += b ;
	 	printf(" test case 01.2: a+b  %9s \n", iToA(a));

	  a = aToI("-9999999999");
	  printf("\n test case 01.3: a     %9s \n", iToA(a));
	  b = aToI("-1");
	 	printf(" test case 01.3: b       %9s \n", iToA(b));
 		a += b ;
	 	printf(" test case 01.3: a+b  %9s \n", iToA(a));

	  a = aToI("-99999999999");
	  printf("\n test case 01.4:  a    %9s \n", iToA(a));
	  b = aToI("-1");
	 	printf(" test case 01.4: b        %9s \n", iToA(b)); 
 		a += b ;
	 	printf(" test case 01.4: a+b  %9s \n", iToA(a));
	  
}


void tc02(){
	 mIntType  a,b,c;

	  a = aToI("-99999999");
	  printf("\n test case 02.1: a    %9s \n", iToA(a));
	  b = aToI("100000000");

	 	printf(" test case 02.1: b     %9s \n", iToA(b));
	 	c = a ;
	 	c+= b; 		
	 	printf(" test case 02.1: a+b  %9s \n", iToA(c));
	 	
	 	c = a ;
	 	c-= b;
		printf(" test case 02.2: a-b  %9s \n", iToA(c));

	 	c = b ;
	 	c-= a;
		printf(" test case 02.3: b-a  %9s \n", iToA(c));
	 	
	 	c = a ;
	 	c += 1 ;
	 	c -= a;
		printf(" test case 02.4: a+1-a  %9s \n", iToA(c));
	 
	  
}

void tc03(){
	 mIntType  a,b,c;

	  a = aToI("-999999999999999");
	  printf("\n test case 03.1: a    %9s \n", iToA(a));
	  b = aToI("1000000000000000");

	 	printf(" test case 03.1: b     %9s \n", iToA(b));
	 	c = a ;
	 	c+= b; 		
	 	printf(" test case 03.1: a+b   %9s \n", iToA(c));
	 	
	 	c = a ;
	 	c-= b;
		printf(" test case 03.2: a-b   %9s \n", iToA(c));

	 	c = b ;
	 	c-= a;
		printf(" test case 03.3: b-a   %9s \n", iToA(c));
	 	
	 	c = a ;
	 	c += 1 ;
	 	c -= a;
		printf(" test case 03.4: a+1-a  %9s \n", iToA(c));
	 
	  
}



void tc1(){
	
	 mIntType  a;
	 
	 
	 
	 a = aToI("91249124791275921569265496124");
	 printf("\n 0 test case 1:  %s \n", iToA(a));
	 
	 a *= 1000;
	 printf("\n   test case 1:  %s \n", iToA(a));
	 a *= 1000000;
	 printf("\n   test case 1:  %s \n", iToA(a));
	 a *= 100000000;
	 printf("\n   test case 1:  %s \n", iToA(a));
	 a *= 1000000000;
	 printf("\n   test case 1:  %s \n", iToA(a));
	
}
#endif

#ifdef GCD
void testGCD()
{
			
		mIntType b = aToI("86189793618632");
		mIntType c = aToI("193719739186189793618632");
		
	
    mIntType gcd, ab, ac;
    extendedGCD(b,c,gcd, ab,ac );
    printf(" b =     %s \n", iToA(b));
    printf(" c =     %s \n", iToA(c));
    printf(" gcd =   %s \n", iToA(gcd));
    printf(" ab =     %s \n",iToA(ab));
    printf(" ac =     %s \n",iToA(ac));

    mIntType c1(b );
    printf(" c1 =  b     %s \n", iToA(c1));
    mIntType c2(c );
    printf(" c2 = c     %s \n", iToA(c2));
    
    mIntType c3((long long) 0 );
    c1 *= ab;
    printf(" c1 *=ab     %s \n", iToA(c1));
    c2 *= ac;
    printf(" c2 *=ac     %s \n", iToA(c2));
    c3 = c1;
    c3 += c2;
    printf(" c3 = c1+c2    %s \n", iToA(c3));
    
    printf("******************************\n");
    if( c3 == gcd ) printf("test passed\n");
    else printf("test failed\n");
    printf("******************************\n");
}
#endif

#ifdef JACOBI
 void testJacobi()
 {
    for (int j = 3; j < 60; j += 2)
        for (int i = 1; i < 31; i++) {
            std::cout << "Jacobi ( ";
            mIntType cj(j);
            mIntType ci(i);
            std::cout << iToString(ci) << "/ ";
            std::cout << iToString(cj) << " ) = ";            
            std::cout << Jacobi( ci, cj) << std::endl;
        }
}
#endif

#if 0 // old debug code
void testMultiplication()
{
	mIntType a, b ;
	a = aToI("987654321") ;
	b = aToI("12345678900") ;
	printf( " a %s\n", iToA(a));
	printf( " b %s\n", iToA(b));
  a *= b;
	printf( "P a*=b %s\n", iToA(a));
	a = aToI("987654321") ;
	a.schoolbookMul( b) ;
	printf( "S a*=b %s\n", iToA(a));
	a = aToI("98765432100000000000000000000000000000") ;
	b = aToI("123456789000000000000000000000000000000") ;
	printf( " a %s\n", iToA(a));
	printf( " b %s\n", iToA(b));
  a *= b;
	printf( "P a*=b %s\n", iToA(a));
	a = aToI("98765432100000000000000000000000000000") ;
	a.schoolbookMul( b) ;
	printf( "S a*=b %s\n", iToA(a));
}
#endif

/* 
    Illustrates the use of the Rand_mIntType class , and shows some ways to massage the output
    to be in the range 0..<seed>
*/
void testRandom()
{
	
#define REPS 50
	 Rand_mIntType r;
	 
	 mIntType a ;   a = aToI("92461924758476912469164612946194691962496124961946");

   std::cout << "    seed  : " << iToString(a) << std::endl ;
	 for (int i = 0 ; i < REPS ; i++){
	 	  mIntType m = r.rand(a);
	 	  std::cout << "     " << std::setw(4) << i << " : " << iToString(m) << std::endl ;
	 }
	 std::cout << std::endl;
	 	
	 	
   std::cout << "    seed  : " << iToString(a) << std::endl ;
	 for (int i = 0 ; i < REPS ; i++){	 	
	 	  mIntType m = r.rand(a);
	 	  while ( m >= a) m >>= 1 ;
	 	  std::cout << "     " << std::setw(4) << i << " : " << iToString(m) << std::endl ;
	 }
	 std::cout << std::endl;
	 		
   std::cout << "    seed  : " << iToString(a) << std::endl ;
	 for (int i = 0 ; i < REPS ; i++){
	 	  mIntType m = r.rand(a);
	 	  while ( m >= a) m %= a;
	 	  std::cout << "     " << std::setw(4) <<i << " : " << iToString(m) << std::endl ;
	 }
	 std::cout << std::endl;

   std::cout << "    seed  : " << iToString(a) << std::endl ;
	 for (int i = 0 ; i < REPS ; i++){
	 	  mIntType m = r.rand1(a);
	 	  std::cout << "     " << std::setw(4) <<i << " : " << iToString(m) << std::endl ;
	 }
	 std::cout << std::endl;
	
}

void testMR1(int &npcount, int &pcount, int width,  mIntType& p)
{
    mIntType prime = p;

    std::string s = iToString(prime);

    if (MillerRabin(prime, 30)) {
        std::cout << std::setw(width+6) << s << " is probably prime " << std::setw(2) <<  ++pcount << std::setw(5) <<  npcount + pcount << std::endl;
    }
    else {
    	  ++npcount;
        //std::cout << std::setw(width +10) << s << " is not prime      " << std::setw(5) <<  ++npcount + pcount <<  std::endl;
    };
}

/* what happened here ?
void testModMul()
{
    mIntType mod; mod = aToI("2147483647");
    mIntType result; result = aToI("4026531840");
    std::cout << "mod : " << iToString(mod) << std::endl;
    std::cout << "result: " << iToString(result) << std::endl;
    result %= mod ;
    std::cout << "result: " << iToString(result) << std::endl;
}

void testModMult()
{
    for (int i = 0; i < COUNT; i++) 
        testModMul();

}

*/

void testMR()
{
    mIntType prime; prime = aToI("26959946667150639794667015087019630673557916260026308143510066298881");

    mIntType prime1; prime1 = aToI("5127821565631733");

   	mIntType prime2; prime2 = aToI("2147483647");
#define WIDTH 75
    int np = 0, p = 0;
    testMR1(np, p, WIDTH, prime2);
    testMR1(np, p, WIDTH, prime1);
    testMR1(np, p, WIDTH, prime2);

    Rand_mIntType Rands;


#define COUNT 1000
#define COUNTMR 9    

    np = 0;
    p = 0;

    mIntType seed(prime);
    seed *= prime ;
	for( int c = 0; c < COUNTMR; c++){    
  	  std::string s = iToString(seed);
    	int w = s.length();
    	std::cout << std::endl<< "seed: "<< std::setw(w) << s <<" (" << std::setw(5) << w <<" digits" <<" ) " <<  std::endl << std::endl;
    	for (int i = 0; i < COUNT; i++) {
      	  mIntType pc = Rands.rand(seed);
        	if (!pc.isOdd()) pc += 1;
        	testMR1(np, p, w, pc);
    	}
    	seed *= 3793  ;  np = 0; p = 0 ;
	}
        
}


void testShiftRight()
{
    mIntType prime; prime = aToI("26959946667150639794667015087019630673557916260026308143510066298881");

    
#ifdef DECIMAL
		std::cout<< " radix 10^9 Shift test"  << std::endl;
#else
		std::cout<< " radix 2^30 Shift test"  << std::endl;
#endif			
    for(int i = 0; i < 230 ; i++){
    	//prime = aToI("26959946667150639794667015087019630673557916260026308143510066298881");
    	prime = aToI("10000000000000000000000000000000000000000000000000000000000000000000");
    	std::cout <<std::setw(5) << i << std::setw(85)  <<  iToString(prime ) << std::endl;
    	prime >>= i ;
    	std::cout << std::setw(5) << i << std::setw(85) <<   iToString(prime ) << std::endl;
    	prime  <<= i ;
    	std::cout <<std::setw(5) << i << std::setw(85) <<   iToString(prime ) << std::endl << std::endl;    		
    }
        
}



#ifdef TONELLISHANKS
void testTonelliShanks()
{
#ifdef PERF
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
    LARGE_INTEGER Frequency;
#endif

    mIntType  P; P = aToI("26959946667150639794667015087019630673557916260026308143510066298881");
    //mIntType  A; A = aToI("18958286285566608000408668544493926415504680968679321075787234672564");
    mIntType  Res;
#define P224 1
#if P224
    // NIST P-224 
    for (int i = 0; i < 5; i++) {
        mIntType t; t = aToI("2021");
        mIntType  A; A = aToI("18958286285566608000408668544493926415504680968679321075787234672564");
        t = t * t * t;
        A += t;
        A += -1*(3 * 2021);
#ifdef PERF
        QueryPerformanceFrequency(&Frequency);
        QueryPerformanceCounter(&StartingTime);
#endif
        if( TonelliShanks(A, P, Res))
        			std::cout<< std::endl<< std::endl << "Root is " << iToString(Res) << std::endl;
#ifdef PERF
        QueryPerformanceCounter(&EndingTime);
        ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
        ElapsedMicroseconds.QuadPart *= 1000000;
        ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
        std::cout << "Elapsed time(microseconds) : " << ElapsedMicroseconds.QuadPart << std::endl;
#endif

        std::cout << std::endl << " A:   " << iToString(A) << std::endl;
        std::cout << " P:   " << iToString(P) << std::endl;
        std::cout << " Res: " << iToString(Res) << std::endl;
        Res = Res * Res;
        std::cout << " Res * Res  : " << iToString(Res)<< std::endl;
        Res %= P ;
        std::cout << " Res * Res  mod P: " << iToString(Res) << std::endl;
    }
    return;
#else
#endif

}
#endif

int main(int argc, char **argv)
{
	      testShiftRight();
	#if 0
	      testTonelliShanks();
	      testMR();
	      //testRandom();
	      //testMultiplication();
	      mIntType x(  863816);
	      mIntType y(29792147);
	      mIntType z ; 
	      z = y + x ; 
	      std::cout << " z "  << iToString(z) << std::endl ;
#ifdef JACOBI	       
	  //testJacobi();
#endif	  
#ifdef GCD
	  testGCD();
#endif
		//testItoAtoI();
	  //tc00();
	  //tc01();
	  //tc02();
	  //tc03();
	  
    //tc1();
	  testMersenne();
//	testItoAtoI();
  	//testShifts();
	
	#endif

}
