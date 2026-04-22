
CC = g++
CFLAGS = -g 
CPPFLAGS =  -O2   -Wwrite-strings

%.o  :  %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm *.o

mInt_ssm.o : mInt_ssm.h mInt_ssm.cpp FFTBase.h FFTClass.h

MontmInt.o : MontmInt.cpp MontmInt.h mInt.h

MontmInt_lib.o : MontmInt_lib.cpp MontmInt_lib.h mInt.h MontmInt.h

mInt.o : mInt.cpp  mInt.h 

mInt.o : mInt.cpp  mInt.h 

mInt_lib.o : mInt_lib.cpp  mInt.h mInt_lib.h 

iToA2.o: iToA2.cpp mInt.cpp mInt.h

mInt_test.o : mInt_test.cpp  mInt.cpp mInt.h iToA2.cpp mInt_lib.h mInt_lib.cpp  mInt_rand.h

mInt_test_min.o : mInt_test_min.cpp  mInt.cpp mInt.h 

mInt_test :  mInt_test.o  mInt.o iToA2.o mInt_lib.o 

mInt_test_min :  mInt_test_min.o  mInt.o

MontmInt_test.o : MontmInt_test.cpp MontmInt.h mInt.h mInt_lib.h

MontmInt_test :  MontmInt_test.o  mInt.o iToA2.o mInt_lib.o MontmInt.o MontmInt_lib.o

mInt_ssmtest :  mInt_test.o  mInt.o iToA2.o mInt_lib.o  mInt_ssm.o
