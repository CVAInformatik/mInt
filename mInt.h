/*
		 another big Integer:    mInt
*/

#include <ctype.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <algorithm>

typedef int baseType;

// the digits are 2s complement integers in the open interval ]-MODULUS...MODULUS[
// this range must leave a one-bit head-room at least, but gives other advantages.
//
// Zero is represented by a number with no digits.
// All digits have the same sign, minus for negative numbers, plus for postive


#define BITSIZE 30
#define BINMODULUS (1 << BITSIZE)
// for DECIMAL bitsize is only 29.897.... bits, 30 will do 
#define DECMODULUS 1000000000

//#define DECIMAL
#ifdef DECIMAL
#define MODULUS DECMODULUS
#else
#define MODULUS BINMODULUS
#endif

class  mIntType;
		
class mIntType 
{

	public:
		static const baseType UL = MODULUS;
		static const baseType LL = (-MODULUS);
		
		// constructors
		mIntType() {val.clear();};
		mIntType(const mIntType &a) {val.clear(); val = a.val ;};
		mIntType(const long long  aint) {
			   long long temp = aint;
			   val.clear();
			   if( aint < 0) temp = -temp;
			   while (temp > 0) {  val.push_back(temp % UL ); temp /= UL; }
			   if( aint < 0) ChangeSign();
				};

    // destructor 
		~mIntType() { val.clear();};  
 		inline mIntType&  operator=( const mIntType &a) { 
 			         if(!( &a == this)) val = a.val; 
 			         	return *this; 
 			        };

		inline void  ChangeSign() { 
			         for(int i = 0; i< val.size(); i++)  val[i] = -val[i]; 
			        };
			        
    inline  int Sign() const { 
    	              if   (val.size() == 0) return 0;
    	 							else if(val.back() > 0) return 1;
    	 							else return -1;
    	           };
                         
 		inline mIntType& operator+=( const mIntType &b ){
 			                int Asign = Sign();
 			                int Bsign = b.Sign();
 			                int ABsign = Asign * Bsign;
 			                if( ABsign){  // both arguments non-zero
 			                	  while( val.size() < b.val.size()) val.push_back(0);
 			                	  for( int i = 0; i < b.val.size(); i++ ) val[i] += b.val[i];
 			                	  doCarry();
 			                	  if( ABsign == -1)  
 			                	  	doNormalize();// not necessary if same signed operands.
  			                }
 			                else if(Bsign) val = b.val ; // b non-zero, a zero 			                	
 			                return *this; 
 			               }; 

    /*
        a -= b implemented as a = -(-a+b) to reuse '+=' code, respecting 'constness' of b
        NB very important special case:  a -= a !
    */
 		inline mIntType& operator-=( const mIntType &b ){
 			 		 if( &b == this) val.clear();// a -= a -> a == 0
 			 		 else {
               ChangeSign(); 
               *this += b ;
               ChangeSign();
           }
           return *this;
         };

			// 'Russian Peasant' algorithm, slow but simple......
 			inline mIntType& operator*=( const mIntType &b )	{
 						mIntType t1,t2 ;
     		 		if( Sign() == 0)  return *this ; // LHS is zero
     		 		// slight speed optimization, fewer shifts and additions (but of larger numbers)-  
     		 		if( val.size() < b.val.size() ){ t2 = *this; 	t1 = b;	}	
     		 		else {t1 = *this; t2 = b; }
      	 		int resign = 1 ;
      	 		if (t1.Sign() < 0) {t1.ChangeSign(), resign = -resign; };
 		  	 		if (t2.Sign() < 0) {t2.ChangeSign(); resign = -resign; };

            val.clear(); // *this = 0;
				 		while(t2.Sign()) {
				  		if( t2.isOdd()) *this += t1 ;
				  		t1 <<= 1;
				  		t2 >>= 1;
				  	}
 		  			if( (resign) < 0) ChangeSign(); 		       
      			return *this;
      		};
 			
 			// better use DivRem() directly, if you need both the quotient and remainder 
 			inline mIntType& operator/=( const mIntType &b ) {
 						 mIntType Div,Rem ;
 						 DivRem( *this, b, Div,Rem);
 						 *this = Div ;
 						 return *this;
 					};
 			
 			inline mIntType& operator%=( const mIntType &b ) {
 						 mIntType Div,Rem ;
 						 DivRem( *this, b, Div,Rem);
 						 *this = Rem ;
 						 return *this;
 					};
      
      // 'unsigned' (or Int-part ) semantics, -1 >>= 1 is 0,  not -1
 			inline mIntType& operator>>=(unsigned int s){
		      	int sign = Sign();
		      	if (sign < 0) ChangeSign();
#ifndef DECIMAL
 			      while (s >BITSIZE )  {  s -=BITSIZE ; divModulus() ;} // binary allows some optimization
#endif 			      	
            while (s-- && val.size() ){
		 			      // we do s one bit shifts.
 			      		for(int j = 1; j < val.size(); j++ ){
 			      			if (val[j] & 1 ) val[j-1] += UL;
 			      			val[j-1] >>= 1 ;	
 			      	  }
 			      		val[val.size()-1] >>= 1;
 			      	  if (val.back() == 0 ) val.pop_back(); 
 			      } 			      	 			    	
 			      if (sign < 0) ChangeSign();
 			      return *this;
 			};

 			inline mIntType& operator<<=(unsigned int _s){ 
 				    for( int i = 0; i < _s ; i++)  *this += *this ;
		      	return *this;
 			};

    	                
    // multiplies with modulus AKA "appending  p zeroes as least significant digits" 
    inline void mulModulus(unsigned int p = 1) { 	
    	      if(val.size() > 0) {
	    	      std::reverse( val.begin(), val.end());
	    	      for( int i = 0 ; i < p ; i++) val.push_back(0);
	    	      std::reverse( val.begin(), val.end());    	       	
    				}
     			};

    // divides with modulus AKA "removing the least p  significant digits" and returning the LSD as result 
    // if number or p  is zero returns UL ( an invalid value for a digit !) as result.        
    //    	                
    inline baseType divModulus(unsigned int p = 1) {  
    	 			baseType res = UL; // not a valid value !
    				if(val.size() > 0) {
    						res = val[0];
	    	      	std::reverse( val.begin(), val.end());
	    	      	if( p >= val.size()) val.clear();
    					  else for( int i = 0 ; i < p ; i++) val.pop_back();
    					  std::reverse( val.begin(), val.end());
    			  }
   				  return res ;
       	 } ;   	                
    								
    // Number of digits in the representation, 0 has no digits, else a positive number.	
    int Digits() const { return val.size(); }			
        													 
    int isOdd() const {if (val.size()) return (val[0] & 1) == 1; else return 0;};													 
    							
		// I would have liked to avoid this friend declaration, but a quick and dirty workaround	reusing old code......
		friend void DivRem(const mIntType &a, const mIntType &m, mIntType &Quotient, mIntType &Remainder );	
	
	private:

		std::vector<baseType> val;
		
		void doCarry(){
			  baseType carry = 0 ;
			  for(int i = 0; i < val.size(); i++){
			       val[i] += carry;
			       if(val[i]>= UL )       { carry =  1 ; val[i] -= UL ;}
			       else if (val[i]<= LL ) { carry = -1 ; val[i] -= LL ;}
			       else carry = 0;
			  }
			  if( carry != 0 ) val.push_back(carry);
			  while( val.size()  && (val.back() == 0)) val.pop_back();
		};
		
		void doNormalize(){
			  baseType carry = 0 ;			  
			  if(val.size() == 0) return ;
			  if(val.back() > 0)
			  	for( int i = 0 ; i < val.size(); i++){
			  		val[i] += carry ;
  	  		  if(val[i] < 0 ){ carry = -1 ;  val[i] += UL; }
  	  		  else carry = 0 ;
			  	}
			  else if (val.back() < 0)
			  	for( int i = 0 ; i < val.size(); i++){
			  		val[i] += carry ;
  	  		  if(val[i] > 0 ){ carry = 1 ;   val[i] -= UL; }
  	  		  else carry = 0;
			  	}
			  while (val.size() && (val.back() == 0)) val.pop_back();
		};

#ifdef VALIDATE
    // usefull for low level debug and validation
    //  Dump of the internal state
		inline  void Dump(char *txt, const std::vector<baseType> &v) const {
			  printf( "\n %s  :\n", txt);
			  if( v.size()) for (int i = 0 ; i < v.size(); i++) 
			    	 printf( "%3d ( hex): %08x  (dec): %9d\n", i, v[i], v[i]);
			  else printf( "    ( hex): %08x  (dec): %9d\n",  0, 0);			  	  	 
			  printf( "**********************\n");
		}
		
		inline  void Dump(char *txt) const {
			  printf( "\n %s  :\n", txt);
			  if( val.size()) for (int i = 0 ; i < val.size(); i++)   
			    			 printf( "%3d ( hex): %08x  (dec): %9d\n", i, val[i], val[i]);
        else 		 printf( "    ( hex): %08x  (dec): %9d\n", 0, 0);
			  printf( "**********************\n");
		}
#endif			
};  //class mIntType 

//
//
//
//
//   The definitions below are not part of the mIntType class,
//   but pretty useful, e.g. if you want to print or read the value of an mInt-instance
//
mIntType aToI(const char *c); 

/* variants of iToA */
#define FORMAT 	"%09d"		
#define GRANULARITY  1000000000
char *iToA(const mIntType &a );
std::string iToString(const mIntType &a ); //experimental faster (when radix is binary) 
	                                     //and more complicated version

// 0 if equal, 1 if a > b, -1 if a < b;
// AKA  Sign() of (a-b) 
int mIntCompare( const mIntType &a, const mIntType &b);

// Nice to have 
inline bool operator==(const mIntType &a, const mIntType &b ) {return 0 == mIntCompare(a,b);}
inline bool operator>=(const mIntType &a, const mIntType &b ) {return -1 != mIntCompare(a,b);}
inline bool operator<=(const mIntType &a, const mIntType &b ) {return 1  != mIntCompare(a,b);}
inline bool operator>(const mIntType &a, const mIntType &b ) {return 1 == mIntCompare(a,b);}
inline bool operator<(const mIntType &a, const mIntType &b ) {return -1  == mIntCompare(a,b);}
inline bool operator!=(const mIntType &a, const mIntType &b ) {return 0 != mIntCompare(a,b);}

/* Fun stuff, applications of mIntType */

void  Mersenne(unsigned int N, mIntType &a );
void _GCD(const mIntType &a, const mIntType &b, mIntType &gcd);

