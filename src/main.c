#include <stdio.h>
#include "ex1.h"

#define NUM_RAWS 2

int main() {
    //u can see if right by running in terminal: lscpu | grep "Byte Order"
	printf("your endin is: %d\n", is_big_endian());

	//testing merge_bytes:
	unsigned long arr[NUM_RAWS][3] ={{0x89ABCDEF12893456, 0x76543210ABCDEF19, 0x89ABCDEFABCDEF19},
	0x0000000000000000, 0x0000000000000000, 0x0000000000000000};

	for(int i = 0; i < NUM_RAWS; ++i) {
		if(arr[i][2] != merge_bytes(arr[i][0], arr[i][1])){
			printf("merge_bytes(0x%lx, 0x%lx) got 0x%lx, expected 0x%lx\n",arr[i][0], arr[i][1], merge_bytes(arr[i][0], arr[i][1]), arr[i][2]);
		}
	}

	unsigned long arr2[NUM_RAWS][4] ={{0x12345678CDEF3456, 0xAB, 2, 0x1234AB78CDEF3456},
	{0x12345678CDEF3456, 0xAB, 0, 0xAB345678CDEF3456}};

	for(int i = 0; i < NUM_RAWS; ++i) {
		if(arr2[i][3] != put_byte(arr2[i][0], (unsigned char) arr2[i][1], (int) arr2[i][2])){	
			printf("put_byte(0x%lx, 0x%lx, %d) got 0x%lx, expected 0x%lx\n",arr2[i][0], arr2[i][1], (int) arr2[i][2], put_byte(arr2[i][0],(unsigned char) arr2[i][1], (int) arr2[i][2]), arr2[i][3]);
		}
	}

	printf("done!\n");
	return 0;
}
