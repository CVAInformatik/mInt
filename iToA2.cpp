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


//
//   New implementation.
//

class iToSfragmentType {

public:
	
		iToSfragmentType( mIntType integer, int sz){			
			fragmentSize = integer;
			fragmentLength = sz ;
		}
	
	  mIntType fragmentSize ;
	  int fragmentLength ;
};


std::vector<iToSfragmentType> iToSStack ; 

void increaseStack()
{
	 mIntType a = iToSStack.back().fragmentSize;
	          a *= a ;
	 int   len =  2*iToSStack.back().fragmentLength;	 
   iToSStack.push_back( iToSfragmentType( a, len )) ;
}

void initStack(){

// 32 zeroes	
#define Z32 	"00000000000000000000000000000000"
	 std::string s= "1" Z32 Z32 Z32 Z32 Z32 Z32 Z32 Z32;
	 	
	 mIntType  a ; a = aToI(s.c_str()) ;	 
	 iToSStack.clear();
	 iToSStack.push_back( iToSfragmentType( a, s.length() ));
	 increaseStack(); 
	 increaseStack(); 
	 increaseStack(); 
	 increaseStack(); 
}

std::string fastItoARec2( const mIntType &a){
	 std::string res = iToA(a);
	 std::reverse( res.begin(),res.end());
	 return res ;	
}

std::string fastItoARec1( unsigned int level, const mIntType &a)
{
	    mIntType Q,R ;
	    std::string res;
	    	
	    DivRem(a,iToSStack[level].fragmentSize, Q, R );

	    if (level > 0) {
  	  		res = fastItoARec1( level-1, R);
  	  		if (Q.Sign() > 0) {
						while ( res.length() < iToSStack[level].fragmentLength) res += "0";
  	  			res  += fastItoARec1( level-1, Q);
  	  		}
	    }
	    else {
     	  	res = fastItoARec2( R);
	  	  	if (Q.Sign() > 0){
						while ( res.length() < iToSStack[0].fragmentLength) res += "0";
  			  	res  += fastItoARec2(Q);	
  			  }
	    }
	    return res ;
}

std::string fastItoARec( const mIntType &a){ return fastItoARec1( iToSStack.size() -1 , a); }

std::string fastItoA(const mIntType &a ) {
	
	 mIntType temp(a); 
	 int sign = temp.Sign();
	 
	 if( sign < 0) temp.ChangeSign();
	 	
   while( temp.Digits() > (2 * iToSStack.back().fragmentSize.Digits()))  increaseStack();
   
   std::string  res =  fastItoARec(a);
   
   if( sign == -1) res += "-";
   	
   std::reverse(res.begin(), res.end());
   
   return res;
}

std::string iToString(const mIntType &a ) 
{
	 std::string res ;
	 
	 if (iToSStack.size() == 0)	 initStack();
	 	
   if(a.Digits()  < iToSStack[0].fragmentSize.Digits())    
   		return iToA(a);
   else 
			res = fastItoA(a);   	
   	    
   return res ;       	
}

#endif