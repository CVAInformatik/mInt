

#include <iostream>
#include "mInt.h"

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
			if (a.Sign()< 0 ) *++d2 = '-';  // add a minus if negative 
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



void  fastItoAaux( unsigned int level, mIntType Int, std::vector< mIntType> divStack, int sz, std::string &res)
{
		mIntType quotient = Int;
		mIntType remainder;
 

	 if(level == divStack.size())
	 	   {	 	   	
	 	   	std::string t = _iToA( Int);	 		 	   	
    		//std::cout << "1 level "<<level<< " res>"  << res << "< t >" << t << "<" <<std::endl;
	 	   	while (t.length() < sz)	t.push_back('0');
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
	 	
   if(BitSize(a) < STRINGLIMIT) 
   	    res = _iToA(a);
   else 
   	    res = fastItoA(a);
   	
	 std::reverse(res.begin(), res.end());	
	 
	 return res;
}

#endif