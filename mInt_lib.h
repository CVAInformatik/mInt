//
//
//
//
//   The definitions below are not part of the mIntType class,
//   but pretty useful, e.g. if you want to print or read the value of an mInt-instance
//



/* variants of iToA */

#define ITOSTRING
std::string iToString(const mIntType &a ); //experimental faster (when radix is binary) 
	                                     //and more complicated version


/* Fun stuff, applications of mIntType */

#define MERSENNE
void  Mersenne(unsigned int N, mIntType &a );

#define GCD
void _GCD(const mIntType &a, const mIntType &b, mIntType &gcd);
void extendedGCD(const mIntType &a, const mIntType &b, mIntType &gcd, mIntType &am, mIntType &bm  );
#define JACOBI
int Jacobi(const mIntType& a, const mIntType& b);
