
CC = g++
CFLAGS = -g 
CPPFLAGS =  -O2   -Wwrite-strings

%.o  :  %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


clean:
	rm *.o

mInt.o : mInt.cpp  mInt.h 

iToA2.o: iToA2.cpp mInt.cpp mInt.h

mInt_test.o : mInt_test.cpp  mInt.cpp mInt.h iToA2.cpp

mInt_test :  mInt_test.o  mInt.o iToA2.o



