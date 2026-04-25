#pragma once
/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

#pragma GCC diagnostic ignored "-Wwrite-strings"

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
// All non-zero digits have the same sign, minus for negative numbers, plus for postive

#define BITSIZE 30
#define BINMODULUS (1 << BITSIZE)
// BINMODULUS is   1073741824 in decimal notation
// for DECIMAL bitsize is only 29.897.... bits, 30 will do 
#define DECMODULUS 1000000000

#define DECIMAL
#ifdef DECIMAL
#define MODULUS DECMODULUS
#else
#define MODULUS BINMODULUS
#endif

// Controls karatsuba like multiplikation, the optimal value 	will depend 
// on application and multiplication algorithm, 
#define KARATSUBALIMIT 150

// Controls SCHOOLBOOK or Russian Peasant multiplikation algorithm
#define SCHOOLBOOK					

//  Controls inclusion of Dump() methods for test and validation
//#define VALIDATE

		
class mIntType 
{
	public:
		static const baseType DIGITSIZE = BITSIZE ;
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

		/*	Do we need this ?	
		mIntType( const std::vector<baseType> v){
			  val.clear();
			  val = v ;
			   // we need to ensure things don't get silly.
			  doCarry();
			  doNormalize(); 
			  // we should now have a proper mInt, with same sign for all non-zero 'digits' 
			  // decided by Most Significant nonzero digit in v
		} */
    
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
    
    //    a -= b implemented as a = -(-a+b) to reuse '+=' code, respecting 'constness' of b.
    //    NB very important special case:  a -= a !    
 		inline mIntType& operator-=( const mIntType &b ){
 			 		 if( &b == this) val.clear();// a -= a -> a == 0
 			 		 else {
               ChangeSign(); 
               *this += b ;
               ChangeSign();
           }
           return *this;
         };

			
 			mIntType& operator*=( const mIntType &b )	{
 						mIntType t1,t2 ;
     		 		if( Sign() == 0)  return *this ; // LHS is zero
#ifdef KARATSUBALIMIT
             // kind of....
						 if( Digits() > KARATSUBALIMIT){
						 	 mIntType t1, t2;
						 	 size_t cut = (val.size() >> 1);
						 	 for(size_t i = 0 ; i < val.size(); i++)
						 	     if( i < cut) t1.val.push_back(val[i]);
						 	     else t2.val.push_back(val[i]);  
						 	 while(t1.val.size() && (t1.val.back() == 0 )) t1.val.pop_back();
						   t1 *= b ; // these are recursive calls for large numbers
						   t2 *= b ; t2.mulModulus(cut);
						   *this = t1;  *this += t2 ;
						 	 return *this;
						 }
						 if( b.Digits() > KARATSUBALIMIT){
						 	 mIntType t1, t2;
						 	 size_t cut = (b.val.size() >>1);
						 	 for(size_t i = 0 ; i < b.val.size(); i++)
						 	     if( i < cut) t1.val.push_back(b.val[i]);
						 	     else t2.val.push_back(b.val[i]);  
						 	 while(t1.val.size() && (t1.val.back() == 0 )) t1.val.pop_back();
						 	 t1 *= *this ; // these are recursive calls for large numbers
						 	 t2 *= *this ; t2.mulModulus(cut);
						 	 *this = t1; *this += t2 ;						 	
						 	 return *this;
						 }
#endif 	
            // Karatsuba falls down here when the numbers are small enough-
#ifndef SCHOOLBOOK
						// 'Russian Peasant' algorithm, slow but simple......
      	 		int resign = 1 ;
     		 		// slight speed optimization, fewer shifts and additions (but of larger numbers)-  
     		 		if( val.size() < b.val.size() ){ t2 = *this; 	t1 = b;	}	
     		 		else {t1 = *this; t2 = b; }
     		 		// signs adjusted, we multiply positive numbers and adjust result last.	
      	 		if (t1.Sign() < 0) {t1.ChangeSign(), resign = -resign; };
 		  	 		if (t2.Sign() < 0) {t2.ChangeSign(); resign = -resign; };
 		  	 		val.clear(); // *this = 0;
 		  	 		// the actual multiplication happens from here 
            while(t2.Sign()) {
				  		if( t2.isOdd()) *this += t1 ;
				  		t1 <<= 1;
				  		t2 >>= 1;
				  	}
 		  			if( (resign) < 0) ChangeSign(); 		       
      			return *this;
#else
            // schoolbook multiplication with a mIntType flavour.
            mIntType _b(b);
            schoolbookMul(_b);
            return *this ;
#endif
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
#ifdef DECIMAL
            // one reason DECIMAL is not universally used 
						while (s >= 9 )  { s -=9 ; shift9() ;} // with radix 10^9 = (5^9)(2^9) we can work 
						                                       // in 9 bit lumps and some 'carry' handling
#else
 			      while (s >= BITSIZE )  {  s -=BITSIZE ; divModulus() ;} // binary allows some optimization
 			                                             // using 30 bit lumps directly
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
 			      dropZeroes();  			      	 			    	
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

    // divides with modulus AKA "removing the least p  significant digits" and returning the original 
    // LSD as result 
    // if number or p  is zero returns UL ( an invalid value for a digit !) as result.        
    inline baseType divModulus(unsigned int p = 1) {  
    	 			baseType res = UL; // not a valid value !
    				if(val.size() > 0) {
    						res = val[0];
	    	      	if( p >= val.size()) val.clear();
    					  else {
				    	      	std::reverse( val.begin(), val.end());
    					  			for( int i = 0 ; i < p ; i++) val.pop_back();
    					  			std::reverse( val.begin(), val.end());
    					  }
    			  }
   				  return res ;
       	 } ;   	                
    								
    // Number of digits in the representation, 0 has no digits, else a positive number.	
    int Digits() const { return val.size(); }			
    // the value of the Least Significant digit or 0 if number is 0
    baseType LSD() const {if (val.size()) return val[0]; else return 0; } 
    // the value of the least significant bit	
    int isOdd() const {if (val.size()) return (val[0] & 1) == 1; else return 0;};													 
    							
		// I would have liked to avoid friend declarations, but a quick and dirty workaround, for re-using old code......
		friend void DivRem(const mIntType &a, const mIntType &m, mIntType &Quotient, mIntType &Remainder );	
	  // Montgomery related friend 
		friend void REDC(  const mIntType &R, const mIntType &N, const mIntType &Ninv, mIntType &a);
	  
	private:

		std::vector<baseType> val;
		
		inline void dropZeroes(){ while (val.size()  && (val.back() == 0) ) val.pop_back(); }
		
		void doCarry(bool skip = false ){
			  baseType carry = 0 ;
			  for(int i = 0; i < val.size(); i++){
			       val[i] += carry;
			       if(val[i]>= UL )       { carry =  1 ; val[i] -= UL ;}
			       else if (val[i]<= LL ) { carry = -1 ; val[i] -= LL ;}
			       else carry = 0;
			  }
			  if( carry != 0 ) val.push_back(carry);
			  if(!skip) dropZeroes();
		};
		
		void doNormalize(){
			  baseType carry = 0 ;			  
			  if(val.size() == 0) return ;
			  if(val.back() > 0)
			  	for( int i = 0 ; i < val.size(); i++){
			  		val[i] += carry ;
  	  		  if(val[i] < 0 ){ carry = -1 ; val[i] += UL; }
  	  		  else carry = 0 ;
			  	}
			  else if (val.back() < 0)
			  	for( int i = 0 ; i < val.size(); i++){
			  		val[i] += carry ;
  	  		  if(val[i] > 0 ){ carry =  1 ; val[i] -= UL; }
  	  		  else carry = 0;
			  	}
			  dropZeroes();
		};
		
#ifdef DECIMAL		
		inline void shift9(){  // assumes a positive number !!
			for( int i = 0 ; i < val.size()-1 ; i++){
				baseType carry  = val[i+1] & 0x1FF ;
				val[i] >>=  9 ;
				val[i] += (UL/512) *carry ;
			}
			val[val.size() -1] >>= 9;
			dropZeroes();
		}
#endif

#ifdef SCHOOLBOOK
	  void schoolbookMul (mIntType b){
            long long a, multiplier  ;            
 						mIntType t1 ;
            int sign = Sign() * b.Sign();
 						if (Sign() == 0) { return;}
 						if (b.Sign() == 0) { val.clear() ; return  ;}
            if( Sign() == -1) ChangeSign();
            if( b.Sign() == -1) b.ChangeSign();
            
            t1 = *this ; std::reverse(t1.val.begin(), t1.val.end());

            val.clear();
            while (val.size() < ((t1.val.size() + b.val.size()) +2) ) val.push_back(0);					 
                   	
            int offset = 0;       	
            while (t1.val.size() ){
            	 multiplier = ( long long ) t1.val.back(); //we begin with LSD, t1 was reversed
            	 t1.val.pop_back();
            	 // we take two passes, first the even digits, 
            	 for(int ib = 0 ; ib < b.val.size(); ib += 2 ){
              	a =  multiplier * b.val[ib]; // a is in the closed range 0..((UL-1)*(UL-1))
#ifdef DECIMAL              	
              	val[ib+offset]   += a%UL ;
              	val[ib+offset+1] += a/UL ;
#else
//some compilers figures this out on their own, when UL is a power of 2
              	val[ib+offset]   += (baseType)( a & ( UL-1)) ; 
               	val[ib+offset+1] += (baseType)( a >> BITSIZE); 
#endif              	
              }
	            doCarry(true); // fixing carries between each product result here
            	 // and then the odd digits, 
            	for(int ib = 1 ; ib < b.val.size(); ib += 2 ){
              	a =  multiplier * b.val[ib]; 
#ifdef DECIMAL              	
              	val[ib+offset]   += a%UL ;
              	val[ib+offset+1] += a/UL ;
#else
              	val[ib+offset]   += (baseType)( a & ( UL-1)) ; 
               	val[ib+offset+1] += (baseType)( a >> BITSIZE); 
#endif              	
              }
	            doCarry(true); // fixing carries between each product result here, again
	            offset++ ;
            } 	
            dropZeroes(); // final clean up
            if(sign == -1) ChangeSign();
            return ;
	  }
#endif	  

#ifdef VALIDATE
    // useful for low level debug and validation
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



// Nice to have, but not essential in, say, an embedded application.
#define FORMAT 	"%09d"		
#define GRANULARITY  1000000000
char *iToA(const mIntType &a );
mIntType aToI(const char *c); 

// Nice to have as an convenience.
inline mIntType operator-( const mIntType a,const mIntType b ){
	   mIntType temp(a);	   temp-= b;	   return temp;}
inline mIntType operator+( const mIntType a,const mIntType b ){
	   mIntType temp(a);	   temp+= b;	   return temp; }
inline mIntType operator*( const mIntType a,const mIntType b ){
	   mIntType temp(a);	   temp*= b;	   return temp;}
inline mIntType operator/( const mIntType a,const mIntType b ){
	   mIntType temp(a);	   temp/= b;	   return temp;}
inline mIntType operator%( const mIntType a,const mIntType b ){
	   mIntType temp(a);	   temp%= b;	   return temp;}

inline bool operator==(const mIntType &a, const mIntType &b ) {return  0 == (a-b).Sign();}
inline bool operator>=(const mIntType &a, const mIntType &b ) {return -1 != (a-b).Sign();}
inline bool operator<=(const mIntType &a, const mIntType &b ) {return  1 != (a-b).Sign();}
inline bool operator>(const mIntType &a, const mIntType &b )  {return  1 == (a-b).Sign();}
inline bool operator<(const mIntType &a, const mIntType &b )  {return -1 == (a-b).Sign();}
inline bool operator!=(const mIntType &a, const mIntType &b ) {return  0 != (a-b).Sign();}
