
#include <stdio.h> 

int main(int argc, char** argv)
{
	
	   	for(int i = 1 ; i < 32; i++){
	   		unsigned int temp = 0x11111111 ;
	   
	   		temp <<= (32- i) ; temp >>= (2);
	   		printf("i %3d  temp  %08X \n", i, temp );
			}
			return 0;
}