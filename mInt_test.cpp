
#include "mInt.h"
#include "mInt_lib.h"

#include <iostream>

void testShifts()
{
	
	mIntType x ;
	for( int i = 0; i < 40 ; i++){
			x = 0x3FFFFFFF;
			printf("\n shift %3d\n",i);
			x <<= i ;
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
#if 0	
   mIntType x ;
   for( int i = 10 ; i < 200; i++){
  			Mersenne( i, x); x.ChangeSign();
  			printf("\n testMersenne  %5d : ", i);
  			printf("%s \n",iToA(x));
  			std::cout << "iToString() "  << iToString(x) << std::endl;
 		}
#endif 		

#define MES(x) do {mIntType y; Mersenne(x,y);std::cout \
	        <<std::endl<<" testMersenne "<< x << " " << iToString(y) << std::endl ;} while (0)		
	        	
  	//		Mersenne( 2000, x); printf("\n testMersenne  %5d : ", 2000);	printf("%s \n",iToA(x));

    //MES(2000);
    //MES(5000);
    //MES(10000);
    //MES(15000);
		MES( 21701); 
		//MES( 44497); 
    //MES( 86243); 

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

int main(int argc, char **argv)
{
	      mIntType x(  863816);
	      mIntType y(29792147);
	      mIntType z ; 
	      z = y + x ; 
	      std::cout << " z "  << iToString(z) << std::endl ;
#ifdef JACOBI	       
	  testJacobi();
#endif	  
	  //testGCD();
		//testItoAtoI();
	  //tc00();
	  //tc01();
	  //tc02();
	  //tc03();
	  
    //tc1();
	  //testMersenne();
//	testItoAtoI();
//	testShifts();
	

}
