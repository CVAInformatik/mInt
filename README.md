mIntType is a big int implementation written for portability (quasi modern C++, no assembly language). I've tried to keep the minmum implementation as small as possible, it is less than 500 LOCs

It uses what I call Signed Signed Magnitude format: Numbers are stored as a std::vector<> of  30 bit signed ints, with same sign on all non-zero digits and a non-zero Most Significant digit.
The mInt Zero is represented by an empty vector. I've found this format surprisingly convenient.

The digits can be either radix 10^9 == 1.000.000.000  (#define DECIMAL)  og radix 2^30 = 1.073.741.824.  DECIMAL has an advantage with regard to I/O speed. 
By using only 30 bits, digitwise addition can't overflow, allowing carry between digits to be postponed to more convenient points in the computation. Examples of this can be found in the '+=' operator implementation and in Schoolbook multiplication.

After addditon of numbers with different signs, it is necessary to 'normalize' the final result ( no leading zero, and same sign on all non-zero digits), but this is a relatively simple matter - 
after carry adjustments, the first non-zero MSD will have the 'true' sign for the number, allowing a simple carry-like  operation to force wayward digits have the proper signs. This step is not neceesary when the numbers added have the same sign.

I've tried to keep the number of 'friends' down, for simplicity reasons. Currently there is one, DivRem().

The simplest version is less than 500 LOC, most of it in mInt.h. It has a simple I/O (which - deliberately - is not part of the class itself) and most of the operators needed for everyday use.
It uses what must be  the simplest version of multiplication known, sometimes called  "Russian Peasant Multiplication", which is not very fast, but still usable for just playing around.

Various 'improvements' (mostly for speed )  can be enabled by #defines : a variant of Karatsuba multiplication and  a variant of Schoolbook multiplication taking advantage of the 30 bit range.
They do not add any functionality to the basic code, just speed improvements ( 'Schoolbook' appears to be 3 times as fast as 'Russian Peasant'). They will push the LOC count up above the 500 LOCs, but not by much.

Apropos speed: Compared to yabInt and pInt, I've tried to keep the number of allocations of temporary mInt copies down, eg.  a-=b is implemented as a =  -(-a+b), reusing the += code and avoiding changing the sign of b.

mInt_test_min.cpp demonstrates this minimal implementation. 

mInt_lib.h/cpp adds a number of library functions ( modular exponentiation, Miller-Rabin primality test, Jacobi-symbol .......), ItoA2.cpp adds iToString() for  faster I/O for the binary radix
and mInt_rand.h adds a very simple radom number generator (used in some mInt_lib functions, like TonelliShanks() (modular squareroot)).

mInt_test.cpp tests/demonstrates the various functions in mInt_lib

April 19th 2026: MontmIntType defined in MontMint.h/cpp A class implementing Montgomery modular arithmetic added with testcases (in MontMint_test.cpp)  demonstrating its use. Fermatnumber F7 is factored in  less than 90 minutes,  a collection of wellknown Mersenne and Fermat composites (including F7) is factored in 95 minutes.

Planned additions:   Schönhage-Strassen FFT multiplication for very large numbers, mostly because I like FFT based algorithms.

Most of the code in the basic mInttype class are simplified versions of  my yabInt/pInt classes, which tended to grow out of hand. Many of the library functions are just ports from these projects. Sometimes also simplified, rather surprisingly, since mIntType - in some ways - is a simpler type.

