/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

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
