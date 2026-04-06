
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
		  c = (char *) malloc(5+(temp.Digits() *10));
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
		
		
void  Mersenne(unsigned int _N,  mIntType &a )
{
	
	  unsigned int N = _N;
	  a = 1 ;
	  while( N >20){
	  	 N -= 20;
	  	 a *= (1024*1024);
	  }
	  while (N--) a <<= 1 ; 
	  a -= 1;
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
			return;
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


void _GCD(const mIntType &a, const mIntType &b, mIntType &gcd)
{
	  if(a.Sign()== 0) { gcd =  0; return ;}
	  if(b.Sign()== 0) { gcd =  0; return ;}
	  
	  unsigned int shift = 0;
	  mIntType _ac(a);
	  mIntType _bc(b);
	  
	  while ( !_ac.isOdd() && !_bc.isOdd()){
	  	 _ac >>= 1;
	  	 _bc >>= 1;
	  	 shift++;
	  }

	  while (!_ac.isOdd()) _ac >>= 1;
	  
    while (_bc.Sign() > 0) {
	 			 while (!_bc.isOdd()) _bc >>= 1;	
				 if( _ac < _bc ) {
	 			 	mIntType swap = _ac ;
	 			 	_ac = _bc;
	 			 	_bc = swap;
	 			 }
	 			 _bc -= _ac;
	 			 _bc >>= 1 ; 
		}
		_ac <<= shift ;
		gcd = mIntType(_ac);
}

#if 0
/*
function extended_gcd(a, b)
    (old_r, r) := (a, b)
    (old_s, s) := (1, 0)
    (old_t, t) := (0, 1)
    
    while r ? 0 do
        quotient := old_r div r
        (old_r, r) := (r, old_r - quotient × r)
        (old_s, s) := (s, old_s - quotient × s)
        (old_t, t) := (t, old_t - quotient × t)
    
    output "Bézout coefficients:", (old_s, old_t)
    output "greatest common divisor:", old_r
    output "quotients by the gcd:", (t, s)
*/

void extendedGCD(const yabIntType &a, const yabIntType &b, yabIntType &gcd, yabIntType &am, yabIntType &bm  )
{
	yabIntType old_r(a);
	yabIntType r(b);
	yabIntType old_s((long long) 1);
	yabIntType s((long long) 0);
	yabIntType old_t((long long) 0);
	yabIntType t((long long) 1);
	
	while(!r.isZero()){
		 yabIntType quotient ;
		 yabIntType rem;
		 DivRem( old_r, r, quotient, rem);
		 { // (old_r, r) := (r, old_r - quotient × r)
		 	  yabIntType temp_oldr(old_r);
		 	  old_r = r;
		 	  r *= quotient ;
		 	  r.ChangeSign();
		 	  r += temp_oldr;		 	  
		 }
		 { // (old_s, s) := (s, old_s - quotient × s)
		 	 yabIntType temp_olds(old_s);
		 	 old_s = s;
		 	 s *= quotient;
		 	 s.ChangeSign();
		 	 s +=  temp_olds;
		 }
		 { //  (old_t, t) := (t, old_t - quotient × t)
		 	  yabIntType temp_oldt(old_t);
		 	  old_t = t;
		 	  t *= quotient;
		 	  t.ChangeSign();
		 	  t += temp_oldt;
		 }		
	}
  gcd = old_r;
	am =  old_s;
	bm =  old_t;	
}

#endif
