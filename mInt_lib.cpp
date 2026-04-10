
#include "mInt.h"
#include "mInt_lib.h"

#ifdef MERSENNE		
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
#endif


#ifdef GCD
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
#endif
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

#define JACOBI
#ifdef JACOBI
//
//  From Wikipedia, with a small change
//
int Jacobi(const mIntType& _a, const mIntType& _n)
{
	 mIntType a(_a);
	 mIntType n(_n);
	
	 if( !n.isOdd()) { printf("Jacobi n must be odd\n"); return 0; }
	 if( n <= 0) 	{    printf("Jacobi n must positive\n"); return 0; }
	 	
	 while ( a < 0 ) a += n;
	 
	 int t = 0;
	 
	 while (a != 0){
	 	while ((a.LSD() & 3) == 0) a >>= 2;
	 	if((a.LSD() & 1) == 0){
	 		 t ^= n.LSD() & 6 ;
	 		 a >>= 1 ;
	 	}
	 	t ^= a.LSD() & n.LSD() & 2 ;
	 	mIntType r(n);
	 	r %= a;
	 	n = a ;
	 	a = r ;
	 }
	 if( n != 1 ) return 0;
	 switch (t)
	 {
	 	  case 2: case 3:
	 	  case 4: case 5:	return -1; break;
	 	  default: return 1 ;
	 }
}
#endif
