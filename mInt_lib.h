/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

//
//   The definitions below are not part of the mIntType class,
//   but pretty useful, e.g. if you want to print or read the value of an mInt-instance
//

/* variants of iToA */

#define ITOSTRING
std::string iToString(const mIntType &a ); //experimental, faster (when radix is binary) 
	                                         //and more complicated version


/* Fun stuff, applications of mIntType */

#define MERSENNE
void  Mersenne(unsigned int N, mIntType &a );

#define GCD
void binGCD(const mIntType &a, const mIntType &b, mIntType &gcd);
void extendedGCD(const mIntType &a, const mIntType &b, mIntType &gcd, mIntType &am, mIntType &bm  );

#define JACOBI
int Jacobi(const mIntType& a, const mIntType& b);

#define MILLERRABIN
bool MillerRabin(const mIntType &number, int witnesses);

#define MODMULTEXP
// Compute (a*b) % mod
mIntType modmult(const mIntType &_a, const mIntType &_b, const mIntType &mod);   
// Compute a^b % mod
mIntType modpow(const mIntType& _a, const mIntType& _b, const mIntType& mod);

#define TONELLISHANKS
// Compute, if possible, res, such that  n == ( res *res) mod p 
// it will return one of the two possible roots, and may return 
// different roots in different runs (the implementation uses a randon number).
bool  TonelliShanks(const mIntType & n, const mIntType& p, mIntType& res);

#define EXPONENTIATION
mIntType exponentiation(int  a, int exp);