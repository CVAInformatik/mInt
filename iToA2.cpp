

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

#if 0

#define STRINGLIMIT 100


/*
    returns a REVERSED string now !
*/
char *_iToA(const mIntType &a ) 
{
			mIntType temp(a) ; 
			mIntType Q ;
			mIntType qt ;
			char *c;
			
			/* special case: 0*/
			if(temp.Sign() == 0)	{c = (char *) malloc(2); sprintf(c, "0");	return c;	}
			
      if( temp.Sign() < 0 ) temp.ChangeSign();
      	
			/* not zero and not negative */			
		  c = (char *) malloc(5+(temp.Digits() *10));
		  memset(c,0, 5+(temp.Digits()*10) );
			char *d = c;	

// we convert in 9 digit lumps			

			do {	
				char buffer[10] ;
	
        mIntType GRAN (GRANULARITY);				
        
        while(temp > GRAN ) {
					qt = temp;
					qt.divModulus();
					if(qt.Sign()== 0) qt = 1;
					Q += qt;
				  qt *= GRAN;
					temp -= qt;
				} 
			  
			  if(temp == GRAN) {
			  	temp -= GRAN;
			  	Q += 1;
			  }
			  
        // here temp is the remainder of  temp%GRANULARITY and Q is temp/GRANULARITY
			  if( temp.Sign() == 0 )
			  	sprintf(buffer,FORMAT, 0);
				else
					 sprintf(buffer,FORMAT, temp.divModulus());
					 
				char *c2 = buffer+8;
				for( int i = 0 ; i < 9 ; i++)	*d++ = *c2--;
				*d = '\0'; 				
				temp = Q;
				Q = 0;
		  } while (temp.Sign() > 0 );

			

		  /* tidy up  and reverse full result */
			char *d1 = c;
			char *d2 = d-1;
			while (*d2 == '0') {*d2-- = 0; }; // drop leading zeroes
			//if (a.Sign()< 0 ) *++d2 = '-';  // add a minus if negative 
			*(d2+1) = 0;// and zero terminate, just to be sure	
			//while (d1 < d2){ 
			// *d1 ^= *d2; // swap values of *d1 and *d2 using three XORs
			// *d2 ^= *d1; 
			// *d1 ^= *d2; 
			//	d1++; d2--;	
			//} 
		  return (char *) realloc(c, 1+strlen(c));
}



/* iToa A optimisation attempt */

//std::vector< yabIntType> divisorstack;
	
void mkDivisors( unsigned int targetsize, unsigned int startSize,mIntType first,   std::vector<mIntType> &stack)	
{

	   if(startSize < targetsize) {
	   	   mIntType t(first);
	   	   t *= first;
	   	   mkDivisors(targetsize, 2*startSize, t, stack);
	   }
	   stack.push_back( first);
}



void  fastItoAaux( unsigned int level, mIntType Int, const std::vector< mIntType> &divStack, int sz, std::string &res)
{
		mIntType quotient = Int;
		mIntType remainder;
 

	 if(level == divStack.size())
	 	   {	 	   	
	 	   	std::string t = _iToA( Int);	 		 	   	
    		std::cout << "1 level "<<level<< " sz "<< sz << std::endl;
    		std::cout << " res>"  << res << "<   t >" << t << "<" <<std::endl;
	 	   	//while (t.length() < sz)	t.push_back('0');
    		//while (t.back() == '0') t.pop_back();
	 	   	res = res + t;
    	}
	 else {
				mIntType t = quotient;			

		  	DivRem(t, divStack[level], quotient, remainder);
			  
				fastItoAaux(level+1, remainder, divStack, sz, res);
				fastItoAaux(level+1, quotient, divStack, sz, res);
	 }

}

/* not really correct, but close enough I hope */
int BitSize(const mIntType &a) {
		return a.Digits() * BITSIZE;
}

std::string fastItoA( mIntType _Int)
{
	
	  mIntType Int(_Int);
#define _divisor "10000000000000000000000000" 
		mIntType divisor = aToI(_divisor);
		std::vector< mIntType> divStack;

		if(_Int.Sign() < 0 ) Int.ChangeSign();
		
 		mkDivisors(BitSize(Int)/2, BitSize(divisor), divisor, divStack);
		std::string result ;	result.clear();
		fastItoAaux(0, Int, divStack, divisor.Digits()-1, result );

		while (result.back() == '0') result.pop_back();
		if(_Int.Sign() < 0 ) result.push_back('-');
			
		return result;		
}


std::string iToString(const mIntType &a ) 
{
	 std::string res ;
	 	
   if(BitSize(a) < STRINGLIMIT) {
   	    return iToA(a);
	 }
   else 
   	    res = fastItoA(a);
   	
	 std::reverse(res.begin(), res.end());	
	 
	 return res;
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
	 iToSStack.push_back( iToSfragmentType( a, s.length()-1 ));
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

#endif