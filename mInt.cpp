/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

#include "mInt.h"


// 0 if equal, 1 if a > b, -1 if a < b;
int mIntCompare( const mIntType &a, const mIntType &b){
   mIntType temp(a)	;
   temp -= b ;
   return temp.Sign();
}

mIntType aToI(const char *c) 
{
        mIntType res ;
			  char *b = (char *)c ;
			  int sign = 0;
		    while( isspace(*b)) b++;
		    if( *b == '-') { sign  = -1; b++;}
		    else if( *b == '+') { sign  = +1; b++;};		    
		    res = 0;
		    while( isdigit(*b))	{		    	
		    	res *= 10 ;
		    	res += (*b -'0') ;
		    	b++;
		    }
		    if( sign < 0 ) res.ChangeSign();
		    return res;
};



char *iToA(const mIntType &a ) 
{
			mIntType temp(a) ; 
			mIntType Q ;
			mIntType qt ;
			char *c;
			
			/* special case: 0*/
			if(temp.Sign() == 0)	{c = (char *) malloc(2); sprintf(c, "0");	return c;	}
			
      if( temp.Sign() < 0 ) temp.ChangeSign();
      	
			/* not zero and not negative */			
		  c = (char *) malloc(5+(temp.Digits() *11));
		  memset(c,0, 5+(temp.Digits()*10) );
			char *d = c;	

// we convert in 9 digit lumps			

			do {	
				char buffer[10] ;
				
#ifdef DECIMAL
				sprintf(buffer,FORMAT, temp.divModulus());			  

				char *c2 = buffer+8;
				for( int i = 0 ; i < 9 ; i++)	*d++ = *c2--;// append, reverse and terminate.
				*d = '\0'; 				
#else

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
#endif				
		  } while (temp.Sign() > 0 );

		  /* tidy up  and reverse full result */
			char *d1 = c;
			char *d2 = d-1;
			while (*d2 == '0') {*d2-- = 0; }; // drop leading zeroes
			if (a.Sign()< 0 ) *++d2 = '-';  // add a minus if negative 
			*(d2+1) = 0;// and zero terminate, just to be sure	
			while (d1 < d2){ 
				 *d1 ^= *d2; // swap values of *d1 and *d2 using three XORs
				 *d2 ^= *d1; 
				 *d1 ^= *d2; 
				 d1++; d2--;	
			} 
		  return (char *) realloc(c, 1+strlen(c));
}

void DivRem(const mIntType &a, const mIntType &m, mIntType &Quotient, mIntType &Remainder )
{
	if (m.Sign() == 0) {
		Quotient = 0 ;
		Remainder = 0;
		return;
	}

	if( (a.Digits() == 1 ) && (m.Digits() == 1 )) // two small numbers
	{
			Quotient = (a.val[0]/m.val[0]);
			Remainder= (a.val[0] % m.val[0]);
/*			if( Remainder.val.size() > 0 )
				printf("1 DivRem  R %d\n", Remainder.val[0]);
			else 
				printf("2 DivRem  R %d\n", 0);
*/			return;
	}
	
	// at least one big number
	mIntType _dividend(a);
	mIntType _divisor(m);
	int reciprocal = m.UL/(2 + m.val.back() );
	int shift = (int) m.Digits();
	mIntType _reciprocal(reciprocal);
	
	Remainder = _reciprocal;
	Remainder *= _dividend;

	if (Remainder.Sign() != 0)  
      for (int i = 0; i < shift; i++) 
      	  switch(Remainder.Digits()){
      	  case 0:   break;
      	  default:  Remainder.divModulus();	break;
     			}
		  
						
	while(1){
			Quotient = Remainder;

		  Remainder *= _divisor;

		  Remainder.ChangeSign();

		  Remainder += _dividend;

      if(Remainder.Sign()  == -1 ){
      	 mIntType r(Remainder);
      	 r.ChangeSign();
      	 if ( _divisor > r ) break;
      } else
      	 if ( _divisor > Remainder ) break;
      	
 			Remainder *= _reciprocal;

      for (int i = 0; i < shift;i++) 
      	  switch(Remainder.Digits() ){
      	  case 0: 	break;
      	  default : Remainder.divModulus();	break;
     			}
		  

		  if(Remainder.Sign() == 0) Remainder = 1;
		  Remainder += Quotient;
	}					
	
	/* clean up */					
	if(Remainder.Sign() == -1){
		 Remainder += _divisor;
		 Quotient  -= 1;
	}		
		
}

