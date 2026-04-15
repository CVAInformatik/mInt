mIntType is a big int implemntation written for portability (quasi modern C++, no assembly language). I've tried to keep the minmum implementation as small as possible, it is less than 500 LOCs

It uses what I call Signed Signed Magnitude format: Numbers are stored as a std::vector<> of  30 bit signed ints, with same sign on all non-zero digits and a non-null Most Significant digit.
The number zero is representated by an empty vector. I've found this format surprisingly convenient.

The digits can be either radix 10^9 == 1.000.000.000  (#define DECIMAL)  og radix 2^30 = 1.073.741.824.  DECIMAL has an advantage with regard to I/O speed. 
By using only 30 bits, digitwise addition can't overflow, allowing carry between digits to be postponed to more convenient points in the computation.

During addditon of numbers with differnnt signs, it is necessary to 'normalize' the final result ( no leading zero, and same sign on all non-zero digits), but this is a relatively simple matter - 
after carry adjustments, the MSD will have the 'true' sign for the number, allowing a simple carry-like  operation to force wayward digits have the proper sign. This step is not neceesary when the
numbers added have the same sign.

The simplest version is less than 500 LOC, most of it in mInt.h. It has a simple I/O (which deliberately is not part of the class itself) and most of the operators needed for everyday use.
It uses what must be  the simplest version of multiplication known, sometimes called  "Russian Peasant Multiplication", which is not very fast, but still usable for just playing around.

Various improvements (mostly for speed )  can be enabled by #defines : a variant of Karatsuba multiplication and  a variant of Schoolbook multiplication taking advantage of the 30 bit range.
They do not add any functionality to the basic code, just speed improvements.

mInt_test_min.cpp demonstrates this minimal implementation.

mInt_lib.h/cpp adds a number of library functions ( modular exponentiatin, MillerRabin primality test,.......)
ItoA2.cpp add faster I/O for binary radix

mInt_rand.h adds a simple radom number generator (used in some mInt_lib functions)

mInt_test.cpp tests/demonstrates the various functions in mInt_lib

Planned extensions:  a class implementing Montgomery multiplication using mInt,  Schönhage-Strassen multiplication for very large numbers.
