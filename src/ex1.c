// 213056153 Nadav Sharabi

#include "ex1.h"

#define NUM_BITS_IN_ONE_BYTE 8
#define BYTE_CONTAINS_NUMBER_ONE 0x01
#define BYTE_ALL_BITS_ARE_ONE 0xFF

/**
 * @brief this func tell you if your
 *  computer using big or little endian.
 * 
 * @return if True (big endian) returns 1,
 *  else (if little endian) return 0.
 */
int is_big_endian() {
    //in bytes 0x0...01
    //in the exercise we are assuming
    //that word is in the size of long.
    unsigned long one = 1;

    //we are getting the byte that is stored in
    //the lowest address cell (from the bytes in 1).
    //we can do it by getting a pointer to one,
    //than we would change the pointer type to unsigned char *,
    //so then we can use *, than whats happens is that we are
    //getting the byte in one that is in the lowest address
    //(because the size of unsigned char is one byte).
    unsigned char firstBit = *((unsigned char *)&one);

    //if the firstByte is 0x01 then the byte in
    //the lowest address of one is LSB so we are in little endian.
    //, else its big endian.
    if(firstBit == BYTE_CONTAINS_NUMBER_ONE){
        return 0;
    }

    return 1;
}

/**
 * This is a helping function to func 2.
 *
 * @return the max value of unsigned long,
 * its mean all the bits are one and in byte,
 * the max value looks like: 0xFF...F
 */
unsigned long getULMax() {
    //here we are getting a new var,
    //that is unsigned long and
    //all his bits are one.
    unsigned long zero = 0;

    //here we are getting the max value,
    //of unsigned long because the not bitwise
    //operation makes all the bits to become one.
    return ~zero;
}

/**
 * This func takes to words and
 * merge them to one word.
 *
 * @param x the first word to merge.
 * @param y the second word to merge.
 *
 * @return the word witch her first half
 * is y (starting from the lsb) and her second half is x.
 */
unsigned long merge_bytes(unsigned long x, unsigned long int y){

    //here we are calculating the size of half unsigned long in bits
    //notice that the sizeof func gives the size in bytes so we are
    //getting the size in bits and than gets only half of it.
    unsigned long halfSizeOfULInBits = (sizeof(unsigned long) * NUM_BITS_IN_ONE_BYTE) / 2;

    //here we are getting the max value of unsigned long
    //so, what we are getting is a var that all of its bits are 1.
    const unsigned long uLMax = getULMax();

    /****here we are calculating the first half****/

    //first, we are using right shift
    //to get var witch his first half is 1 and the other is 0 in binary
    //the number should lock like this: 00....011...1
    unsigned long firstHalf = uLMax>>halfSizeOfULInBits;

    //now we are using the and bitwise operator
    //so, because the first half of firstHalf
    //is 1 and the other is 0 only the bits in the first half of y
    //are being saved in the result and the other half is 0.
    firstHalf = y & firstHalf;

    /****here we are calculating the second half****/

    //first, we are using left shift
    //to get var witch his second half is 1 and the first half
    //is 0 in binary the number should lock like this: 11...100...0
    unsigned long secondHalf = uLMax<<halfSizeOfULInBits;

    //now we are using the and bitwise operator
    //so, because the second half of secondHalf
    //is 1 and the first half is 0 only the bits in the second half of x
    //are being saved in the result and the first half is 0.
    secondHalf = x & secondHalf;

    /****here we are calculating the result****/

    //now we have the firstHalf and the secondHalf of the result
    //so, if the result should be in binary: rr..r
    //the firstHalf = 00...0rr..r
    //the secondHalf = rr..r00..0
    //so the or bitwise would merge the bits as expected to the result.
    return (firstHalf | secondHalf);
}

/**
 * helping func to func 3.
 *
 * @param b a byte.
 * @param i the index to move b.
 * @return returns an unsigned long var,
 * witch his w/8 - 1 - i byte is b and all his other bytes
 * are 0x00.
 * (w = the length of a word (unsigned long) in bites)
 */
unsigned long moveBitsToLoc(unsigned char b, int i){
    //here we are calculating the length of a word in bits.
    //notice the sizeof func return the length in
    //bytes and we need to convert it to bits.
    unsigned long wordSizeInBits = NUM_BITS_IN_ONE_BYTE * sizeof(unsigned long);

    //here we firs extend b to unsigned long so noe we have a var witch all his
    //bytes are 0 but the lsb is b. than we want him to be the
    //w/8 - 1 - i byte, but he is the 0 (location) byte
    //so we need to do left shift (w/8 - 1 - i) * NUM_BITS_IN_ONE_BYTE
    //because this way we move b (w/8 - 1 - i) bytes and making him the
    //(w/8 - 1 - i) in the result
    return ((unsigned long) b) << (wordSizeInBits -
    NUM_BITS_IN_ONE_BYTE - NUM_BITS_IN_ONE_BYTE * i);
}

/**
 * Switching the w/8 - 1 - i byte in x with the byte
 * b and returning the result.
 * (w = the length of a word in bits =  the length of x in bits)
 *
 * @param x the word to switch a byte in.
 * @param b the byte to put.
 * @param i to switch the w/8 - 1 - i byte in x.
 * @return the word witch the w/8 - 1 - i byte in x is
 * switched with the byte b.
 */
unsigned long put_byte(unsigned long x, unsigned char b, int i){

    //if i is not between 0 and w/8 - 1
    //(w/8 = the size of x in bytes = sizeof(unsigned long))
    //so this is not a valid index (out of range index),
    //because the index is out of his range we wouldn't
    //change any byte in x, and return x as is.
    if(i < 0 || i > (sizeof(unsigned long) - 1)){
        return x;
    }

    //first we taking a byte witch all of his bits are 1 and
    //push him to the w/8 - 1 - i byte, and the other bytes will be 0x00
    //we are marking the bits we want to change in x, than by the nor bitwise
    //operator we are marking witch bits x should save (by 1) and witch not (bt 0).
    unsigned long bitsToSave = ~(moveBitsToLoc(BYTE_ALL_BITS_ARE_ONE, i));

    //now we are using the and bitwise operator
    //on x and the bitsToSave so all the bits who marked to
    //be saved are now being saved and the bits who are marked not to be saved
    //(because they are in the location that should be switched) are still 0.
    unsigned long bitsInXToSave = x & bitsToSave;

    //now we are getting the b byte and push him to the
    //w/8 - 1 - i byte, and the other bytes will be 0x00
    //by using moveBitsToLoc(b, i). Also, in bitsInXToSave
    // we have all the bits in x that need to be saved
    // and the other are 0. So, all we need now is to use
    //the or bitwise operator to merge the part to the full result.
    return (bitsInXToSave | moveBitsToLoc(b, i));
}