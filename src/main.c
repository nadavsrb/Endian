#include <stdio.h>
#include "ex1.h"

#define NUM_RAWS 7

int main() {
    //u can see if right by running in terminal: lscpu | grep "Byte Order"
	printf("your endin is: %d\n", is_big_endian());

	//testing merge_bytes:
	unsigned long arr[NUM_RAWS][3] ={{0x89ABCDEF12893456, 0x76543210ABCDEF19, 0x89ABCDEFABCDEF19},
                                     {0x0000000000000000, 0x0000000000000000, 0x0000000000000000},
                                     {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
                                     {0xFABC2349762FEABC, 0x1729FFABEB2546EE, 0xFABC2349EB2546EE},
                                     {0x2050607080901050, 0xFFFFFFAAABBBCCCE, 0x20506070ABBBCCCE},
                                     {0x0001000000000000, 0x0000000000010000, 0x0001000000010000},
                                     {0x0000000000000FF0, 0x00000FF000000000, 0x0000000000000000}};

	for(int i = 0; i < NUM_RAWS; ++i) {
		if(arr[i][2] != merge_bytes(arr[i][0], arr[i][1])){
			printf("merge_bytes(0x%lx, 0x%lx) got 0x%lx, expected 0x%lx\n",
          arr[i][0], arr[i][1], merge_bytes(arr[i][0], arr[i][1]), arr[i][2]);
		}
	}

	unsigned long arr2[NUM_RAWS][4] ={{0x12345678CDEF3456, 0xAB, 2, 0x1234AB78CDEF3456},
                                      {0x12345678CDEF3456, 0xAB, 0, 0xAB345678CDEF3456},
                                      {0x0000000000000000, 0xAB, 0, 0xAB00000000000000},
                                      {0x0213456789101112, 0x00, 5, 0x0213456789001112},
                                      {0x0000100000001000, 0xAB, 0, 0xAB00100000001000},
                                      {0x0000000000000001, 0xAB, 7, 0x00000000000000AB},
                                      {0x0100101000100000, 0xCC, 6, 0x010010100010CC00}};

	for(int i = 0; i < NUM_RAWS; ++i) {
		if(arr2[i][3] != put_byte(arr2[i][0], (unsigned char) arr2[i][1], (int) arr2[i][2])){	
			printf("put_byte(0x%lx, 0x%lx, %d) got 0x%lx, expected 0x%lx\n",
          arr2[i][0], arr2[i][1], (int) arr2[i][2],
          put_byte(arr2[i][0],(unsigned char) arr2[i][1], (int) arr2[i][2]), arr2[i][3]);
		}
	}

	//testing special inputs:
    unsigned long arr3[2][4] ={{0x12345678CDEF3456, 0xAB, -1, 0x12345678CDEF3456},
                                      {0x12345678CDEF3456, 0xAB, 8, 0x12345678CDEF3456}};

    for(int i = 0; i < 2; ++i) {
        if(arr3[i][3] != put_byte(arr3[i][0], (unsigned char) arr3[i][1], (int) arr3[i][2])){
            printf("put_byte(0x%lx, 0x%lx, %d) got 0x%lx, expected 0x%lx\n",
                   arr3[i][0], arr3[i][1], (int) arr3[i][2],
                   put_byte(arr3[i][0],(unsigned char) arr3[i][1], (int) arr3[i][2]), arr3[i][3]);
        }
    }

    printf("done!\n");
	return 0;
}
