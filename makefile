
CC = g++
CFLAGS = -g 
CPPFLAGS =  -O2   -Wwrite-strings

%.o  :  %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm *.o

mInt.o : mInt.cpp  mInt.h 

mInt.o : mInt.cpp  mInt.h 

mInt_lib.o : mInt_lib.cpp  mInt.h mInt_lib.h 

iToA2.o: iToA2.cpp mInt.cpp mInt.h

mInt_test.o : mInt_test.cpp  mInt.cpp mInt.h iToA2.cpp mInt_lib.h mInt_lib.cpp

mInt_test_min.o : mInt_test_min.cpp  mInt.cpp mInt.h 

mInt_test :  mInt_test.o  mInt.o iToA2.o mInt_lib.o

mInt_test_min :  mInt_test_min.o  mInt.o


