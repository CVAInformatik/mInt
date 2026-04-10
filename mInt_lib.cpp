
#include "mInt.h"

#if 0

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
#endif		
		
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

#if 1
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

void extendedGCD(const mIntType &a, const mIntType &b, mIntType &gcd, mIntType &am, mIntType &bm  )
{
	mIntType old_r(a);
	mIntType r(b);
	mIntType old_s((long long) 1);
	mIntType s((long long) 0);
	mIntType old_t((long long) 0);
	mIntType t((long long) 1);
	
	while(!r.Sign() == 0){
		 mIntType quotient ;
		 mIntType rem;
		 DivRem( old_r, r, quotient, rem);
		 { // (old_r, r) := (r, old_r - quotient × r)
		 	  mIntType temp_oldr(old_r);
		 	  old_r = r;
		 	  r *= quotient ;
		 	  r.ChangeSign();
		 	  r += temp_oldr;		 	  
		 }
		 { // (old_s, s) := (s, old_s - quotient × s)
		 	 mIntType temp_olds(old_s);
		 	 old_s = s;
		 	 s *= quotient;
		 	 s.ChangeSign();
		 	 s +=  temp_olds;
		 }
		 { //  (old_t, t) := (t, old_t - quotient × t)
		 	  mIntType temp_oldt(old_t);
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

#if 0
int Jacobi(const mIntType& a, const mIntType& b)
{

	mIntType A(a);
	mIntType M(b);
	int ResSign = 1;
	if (M.Sign() == 0)
		return 1;
	else {
		mIntType rem, quotient;

	  DivRem(A, M, quotient, rem); A = rem;
		if (rem.Sign()== 0) {  //A|M 
			printf( " A %s M %s quotient %s  rem %s \n", iToA(A), iToA(M), iToA(quotient), iToA(rem) );
			return 0;
		}
		else {
			while (A.Sign() != 0) {
				while ((A.Sign() != 0) && (!A.isOdd()))
				{
					A>>= 1;
					switch (M.LSD() & 0x7)
					{
					case 3: 
          case 5:   
               ResSign = -ResSign;
						break;
					default:
						break;
					}
				}
				mIntType temp(A);
				A = M;
				M = temp;
				if ((A.Sign() != 0) && (M.Sign() != 0 ) && (3 == (A.LSD() & 0x3)) && (3 == (M.LSD() & 0x3))) 
                    ResSign = -ResSign;
        DivRem(A, M, quotient, rem); A = rem;

			}
			if ((M.Digits() == 1) && (M.isOdd()))
				return ResSign;
			else
				return 0;
		}
	}
};
#elif 1

int Jacobi(const mIntType& a, const mIntType& b)
{
   return 1;
}
#endif