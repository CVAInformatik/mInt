

#include <iostream>
#include "mInt.h"

#define FORMAT 	"%09d"		
#define GRANULARITY  1000000000


#ifdef DECIMAL
std::string iToString(const mIntType &a ) 
{	
	   mIntType temp(a);
	   std::string res ;
      
     if( a.Sign() == 0) { res = "0"; return res; }
     	
     if( temp.Sign() < 0) temp.ChangeSign();
     do {
     	  char buffer[10] ;
				sprintf(buffer,FORMAT, temp.divModulus());			  
				char *c2 = buffer+8;
				char *d  = buffer;
				while ( d < c2){
					*d ^= *c2;
					*c2 ^= *d;
					*d ^= *c2;
					d++ ; c2--;
				}							
        
        if (temp.Sign() == 0){ // last digit
        	char *d1 = buffer+8 ;
        	while (*d1 == '0') { *d1-- = 0;}
        }
        res = res + buffer ;
     }
     while(temp.Sign() > 0);

     if( a.Sign() < 0 ) res = res + "-";

     std::reverse(res.begin(), res.end());	   	
	   
	   return res ;
}

#else



#define STRINGLIMIT 100

/* major rework in progress, sorry ! */

std::string iToString(const mIntType &a ) 
{
   	    return iToA(a);
}

#endif
