// 213056153 Nadav Sharabi
#include "ex1.h";

#include <stdint.h>
#include <limits.h>

int is_big_endian() {
    //in bytes 0x0...01
    //in the exercise we are assuming
    // that word is in the size of long.
    long one = 1;

    //we are getting the byte that is stored in
    //the lowest address cell (from the bytes in 1).
    //we can do it by getting a pointer to one,
    //than we would change the pointer type to uint_8 *,
    //so then we can use *, than whats happens is that we are
    //getting the byte in one that is in the lowest address.
    uint8_t firtBit = *((uint8_t *)&one);

    //if the firstByte is 0x01 then the byte in
    //the lowest address of one is LSB so we are in little endian.
    //, else its big endian.
    if(firtBit == 0x01){
        return 0;
    }

    return 1;
}

unsigned long merge_bytes(unsigned long x, unsigned long int y){
    unsigned long halfSizeOfULInBites = (sizeof(unsigned long) * 8) / 2;

    unsigned long firstHalf = ULONG_MAX>>halfSizeOfULInBites;
    unsigned long secondHalf = ULONG_MAX<<halfSizeOfULInBites;

    firstHalf = y & firstHalf;
    secondHalf = x & secondHalf;

    return (firstHalf | secondHalf);
}

unsigned long moveBitesToLoc(unsigned char b, int i){ //helping func
    unsigned long wordSizeInBites = 8 * sizeof(unsigned long);

    return ((unsigned long) b) << (wordSizeInBites - 8 - 8 * i);
}

unsigned long put_byte(unsigned long x, unsigned char b, int i){
    unsigned long bitsToSave = ~(moveBitesToLoc(0xFF, i));

    x = x & bitsToSave;

    x = x | (moveBitesToLoc(b, i));

    return x;
}