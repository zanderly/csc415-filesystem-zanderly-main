/**************************************************************
* Class:  CSC-415-03# Fall 2022
* Names: Issa Shihadeh, Alexander Bjeldanes, Elias Abay, Janvi Patel
* Student IDs: 921889667, 921583764, 917150252, 917944864
* GitHub Name: Issashihadeh, zanderly, pjanvi22, eabay98
* Group Name: Atomic
* Project: Basic File System
*
* File: fsFreeSpace.c
*
* Description: Free Space management functions to handle our bitmap
*
**************************************************************/


#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#include "fsLow.h"
#include "mfs.h"


#define FULL_BYTE 255	// Value of a byte with all bits set to 1

extern VCB* vcb;
extern int err;
void setBit(u_int8_t* byte, u_int8_t bit) {
	bit = 1 << bit;		// set the bitmask
	*byte |= bit;		// OR byte with the bitmask
}

void unsetBit(u_int8_t* byte, u_int8_t bit) {
	bit = 1 << bit;		// set the bitmask
	bit ^= 0xFF;		// XOR with 0xFF to invert the bitmask
	*byte &= bit;		// AND byte with the bitmask
}

int isBitFree(u_int8_t byte, u_int8_t bit) {
	bit = 1 << bit;				// set the bitmask
	if((byte & bit) == 0) {		// if byte & bit == 0, the bit is free
		return 1;
	}
	else {
		return 0;
	}
}


u_int8_t allocBlocks(int count) {
	int found = 0; // number of free blocks found
	int index = 0; // index in startOfFreeSpace we are on
	u_int8_t prevFree = 0; // previous bit number to check for contiguous allocation
	u_int8_t bitNum = 0; // bit number we are on, which corresponds to LBA

	// Loop while there are more blocks requested and there are more blocks to check
	while(found < count && index < vcb->freeLen) {
		// Check if the startOfFreeSpace byte has all of its bits set to 1
		if(vcb->startOfFreeSpace[index] != 255) {
			// If not, loop through its bits
			for(int i = 0; i < 8; i++) {
				// Check if the bit is free
				if(isBitFree(vcb->startOfFreeSpace[index], i)) {
					if(prevFree == bitNum - 1) {	// If the previous free bit was the one before
						found++;					// this, increment found and set prevFree to
						prevFree = bitNum;			// this bit number.
					}
					else {					// If the previous free bit was not the one before this,
						found = 1;			// then they are not contiguous.  Set found to 1 and
						prevFree = bitNum;	// prevFree to this bit number
					}

				}
				if(found == count) {
					break;		// Exit the loop if we have found enough free blocks
				}
				bitNum++;
			}
		}
		// If the byte was full, increment bitNum by 8
		else {
			bitNum += 8;
		}

		index++;
	}

	// Check if we have found the number of blocks requested
	if(found == count) {
		// Set bitNum to the starting index of blocks to be allocated
		bitNum = prevFree - count + 1;

		// Set allocated bits to 1
		for(int i = 0; i < count; i++) {
			// Get index of the byte we need
			index = (bitNum + i) / 8;
			// Get the bit we need
			u_int8_t bit = (bitNum + i) % 8;
			setBit(&vcb->startOfFreeSpace[index], bit);
		}

		// Write the updated startOfFreeSpace to disk
		int ret = LBAwrite(vcb->startOfFreeSpace, vcb->startOfFSBlock, vcb->freeMapAddress);
		if(ret != vcb->startOfFSBlock) {
			err = errno;
			perror("allocBlocks");
			return 0;
		}
	}
	// If we did not find enough free blocks, set bitNum to 0 to indicate this
	else {
		bitNum = 0;
	}

	return bitNum;
}

int freeBlocks(u_int8_t addr, int count) {
	int index;
	u_int8_t bit;
	for(int i = 0; i < count; i++) {
		index = (addr + i) / 8;
		bit = (addr + i) % 8;
		unsetBit(&vcb->startOfFreeSpace[index], bit);
	}

	LBAwrite(vcb->startOfFreeSpace, vcb->startOfFSBlock, vcb->freeMapAddress);

	return 1;
}
