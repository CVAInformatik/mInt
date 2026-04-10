
#include "mInt.h"

#include <iostream>

void testShifts()
{
	
	mIntType x ;
	printf("\n test shifts \n" );
	for( int i = 0; i < 40 ; i++){
			x = 0x3FFFFFFF;
			printf("shift %3d ",i);
			x <<= i ;
			printf(" %s ",iToA(x));
			x >>= i ;
			printf(" %s \n",iToA(x));
	}
}


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




int main(int argc, char **argv)
{
	      mIntType x(  863816);
	      mIntType y(29792147);
	      mIntType z ; 
	      z = y + x ; 
	      printf(" z %s\n", iToA(z));
	      
	  tc00();
	  tc01();
	  tc02();
	  tc03();
	  
    tc1();
		
		testShifts();
	/**/

}
