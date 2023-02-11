/**************************************************************
* Class:  CSC-415-03# Fall 2022
* Names: Issa Shihadeh, Alexander Bjeldanes, Elias Abay, Janvi Patel
* Student IDs: 921889667, 921583764, 917150252, 917944864
* GitHub Name: Issashihadeh, zanderly, pjanvi22, eabay98
* Group Name: Atomic
* Project: Basic File System
*
* File: fsInit.c
*
* Description: Main driver for file system assignment.
*
* This file is where you will start and initialize your system
*
**************************************************************/


#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include "fsLow.h"
#include "mfs.h"
#include "fsFreeSpace.c"

#define DIRECTORY_ENTRIES 50 //using 50 untries
#define MAGICNUMBER 0x796A616C6A6A616E // declaring the signature
#define DIRECTORY_SIZE 60 // declaring the directory size
#define FREESPACE_BLOCKS 5 // declaring free space blocks
#define BITS_COUNT 19531 // using 19531 bits

int initVCB(uint64_t, uint64_t, uint64_t);
int initFreespace(int);
int initFreeSpace();
int initRootDir();
int err;
u_int8_t* bitV;	// Pointer will be to the bitvector we are using for our free map
int initRootDir(VCB*, Entry*, uint64_t);
VCB* vcb;

struct BITMAP{ // using bitmap
	unsigned value : 1;
}bit[BITS_COUNT];

/*struct VCB vcb = {
	.magicNumber = 0101010
};*/  

/*VCB getVCB() // vcb getter 
{
	return vcb;
}*/

VCB *vcbSpace;
int *freespace;


// int initVCB(uint64_t numberOfBlocks, uint64_t blockSize, uint64_t vcbPointer){
// 	// 	intializing the known variables to the volume control block
// 	VCB.blockSize = blockSize;
// 	VCB.numberOfFreeBlocks = numberOfBlocks;
// 	VCB.magicNumber = MAGICNUMBER;



// 	return 0;
// }

int initFreespace(int numberOfBlocks){

// 	//uint64_t *freeSpace = (uint64_t *)malloc(sizeof(FREESPACE_BLOCKS * blockSize));
// 	//freespace
// 	if(free)
// 	LBAwrite(freeSpace, FREESPACE_BLOCKS, 1);
// 	vcb.startOfFSBlock = 1;
// 	vcb.startOfFreeSpace = FREESPACE_BLOCKS + 1; 

// 	for (int i = 0; i < numberOfBlocks; i++) // looping through the blocks
// 	{
// 	bit[vcb.startOfFreeSpace].value = 1; // setting the value to 1 because is free in bitmap
// 	vcb.startOfFreeSpace++; // incrementing the free space 
// 	}
// 	return 0;
	int freeSpace = vcb->mapBlocks * vcb->blockSize;
	bitV = calloc(freeSpace,sizeof(*bitV));
	if(bitV == NULL){
		err = errno;
		perror("Error, bitV");
		return err;
	}
	int voidBits = freeSpace * 8 - vcb->mapBlocks;
	int voidBytes = voidBits / 8;
	voidBits = voidBytes % 8;

	for(int i = 1; i <= voidBytes; i++) {
		bitV[freeSpace - i] = FULL_BYTE;
	}

	for (int i = 0; i <= voidBits; i++){
		u_int8_t bit = 8 - (voidBits - i);
		setBit(&bitV[freeSpace - (voidBytes + 1)], i);
	}
	
	setBit(&bitV[0], 0);
	for(int i = 1; i <= vcb->mapBlocks; i++) {
		setBit(&bitV[0], i);
	}
	int ret = LBAwrite (bitV, vcb->mapBlocks, vcb->freeMapAddress);
	if(ret != vcb->mapBlocks){
		err = errno;
		perror("Error, initFreeSpace");
		return err;
	}
	vcb->freeMap = (uint64_t)bitV;
	return 1;
	
 }


// int initRootDir(){
// 	float rootDirectorySpace = DIRECTORY_SIZE * DIRECTORY_ENTRIES;
// 	float rootDirectoryBlocks = (rootDirectorySpace / blockSize) * 10.0;
// 	int numberOfDirectoryBlocks = rootDirectoryBlocks / 10;
	
// 	if(((int)rootDirectoryBlocks % 10) > 0){
// 		numberOfDirectoryBlocks += 1;
// 	}
// 		// declaring the root Directory Size
// 	int rootDirectorySize = (blockSize * numberOfDirectoryBlocks);
		
// 		// declaring the number Of Directory Entries
// 	int numberOfDirectoryEntries = rootDirectoryBlocks / DIRECTORY_SIZE;
		
// 		// allocating memory to the pointer of root directory 
// 	uint64_t  *rootDirectory = (uint64_t *)malloc(sizeof(rootDirectorySpace));
		
// 		// updating the start of the root 
// 	vcb.startOfRoot = (vcb.startOfFreeSpace + FREESPACE_BLOCKS);
	
// 	// looping through directory entries 
// 	for (int i = 0; i < numberOfDirectoryEntries; i++){
// 		Entry freeState; 
// 		freeState.id = 0; // kill free state
// 	}
// 	LBAwrite(vcbPointer, 1, 0);//writing to disk 
	 
// 	return 0;
// }



//=======



// int initVCB(uint64_t numberOfBlocks, uint64_t blockSize, uint64_t vcbPointer){
// 	// 	intializing the known variables to the volume control block
// 	// VCB.blockSize = blockSize;
// 	// VCB.numberOfFreeBlocks = numberOfBlocks;
// 	// VCB.magicNumber = MAGICNUMBER;

// 	memset(vcbSpace, 0, sizepf(VCB));
// 	vcbSpace->magicNumber = MAGICNUMBER;
// 	vcbSpace->blockSize = blockSize;
// 	vcbSpace->numberOfBlocks = numberOfBlocks;



// 	return 0;
// }

int initFreeSpace(){

	// freespace = malloc(vcbSpace->numberOfBlocks);
	// if(freespace == NULL){
	// 	perror("malloc freespace");
	// 	return errno;
	// }
	// memset(freespace, 0, vcbSpace->numberOfBlocks);
	// return 0;
	
	//uint64_t *freeSpace = (uint64_t *)malloc(sizeof(FREESPACE_BLOCKS * blockSize));
	//freespace
	// if(free)
	// LBAwrite(freeSpace, FREESPACE_BLOCKS, 1);
	// vcb.startOfFSBlock = 1;
	// vcb.startOfFreeSpace = FREESPACE_BLOCKS + 1; 

	// for (int i = 0; i < numberOfBlocks; i++) // looping through the blocks
	// {
		// bit[vcb.startOfFreeSpace].value = 1; // setting the value to 1 because is free in bitmap
		// vcb.startOfFreeSpace++; // incrementing the free space 
	// }
	
	return 0;
}



int initRootDir(VCB *vcbPointer, Entry *rootD, uint64_t bitMapSize){

	

// 	float rootDirectorySpace = DIRECTORY_SIZE * DIRECTORY_ENTRIES;
// 	float rootDirectoryBlocks = (rootDirectorySpace / blockSize) * 10.0;
// 	int numberOfDirectoryBlocks = rootDirectoryBlocks / 10;
	
// 	if(((int)rootDirectoryBlocks % 10) > 0){
// 		numberOfDirectoryBlocks += 1;
// 	}
// 		// declaring the root Directory Size
// 	int rootDirectorySize = (blockSize * numberOfDirectoryBlocks);
		
// 		// declaring the number Of Directory Entries
// 	int numberOfDirectoryEntries = rootDirectoryBlocks / DIRECTORY_SIZE;
		
// 		// allocating memory to the pointer of root directory 
// 	uint64_t  *rootDirectory = (uint64_t *)malloc(sizeof(rootDirectorySpace));
		
// 		// updating the start of the root 
// 	vcb.startOfRoot = (vcb.startOfFreeSpace + FREESPACE_BLOCKS);
	
// 	// looping through directory entries 
// 	for (int i = 0; i < numberOfDirectoryEntries; i++){
// 		Entry freeState; 
// 		freeState.id = 0; // kill free state
// 	}
// 	LBAwrite(vcbPointer, 1, 0);//writing to disk 
	 
// 	return 0;
}




int initFileSystem (uint64_t numberOfBlocks, uint64_t blockSize)
	{
	
	/* TODO: Add any code you need to initialize your file system. */
		//malloc memory block as a pointer

	//VCB *vcbPointer = (VCB *)malloc(sizeof(VCB)); 
	u_int64_t vcbPointer = sizeof(VCB) / blockSize;
	if ((sizeof(VCB) % blockSize) > 0){
		vcbPointer++;
	}
	
		//starting at block '0'
	uint64_t * buffer = (uint64_t *)malloc(blockSize);
	if(buffer == NULL){
		perror("malloc buffer for block 0 failed");
		return errno;
	}

	//LBAread(buffer, 1, 0);
	LBAread(buffer, vcbPointer, 0);

	//allocate space for vcb and copy data from buffer into VCB
	vcbSpace = malloc(sizeof(VCB));
	if(vcbSpace == NULL){
		perror("malloc() vcbSpace");
		return errno;
	}
	memcpy(vcbSpace, buffer, sizeof(VCB));

	free(buffer);
	buffer = NULL;

	printf ("Initializing File System with %ld blocks with a block size of %ld\n", 	 	
		numberOfBlocks, blockSize);
        int ret = 0;

		//incase the the signature is differnet, initialize again
	if(vcbSpace->magicNumber == MAGICNUMBER){

		buffer = malloc(vcbSpace->numberOfBlocks * vcbSpace->blockSize);
		if(buffer == NULL){
			perror(" malloc() buffer for vcb");
			return errno;
		}
		//LBAread(buffer, vcbSpace->numberOfFreeBlocks, vcbSpace->)

		//copy data into freespace
		freespace = malloc(vcbSpace->numberOfBlocks);
		if(freespace == NULL){
			perror("malloc freespace");
			return errno;
		}
		memcpy(freespace, buffer, vcbSpace->numberOfBlocks);

		//cleanup buffer
		free(buffer);
		buffer == NULL;

		// int blockCount = sizeof(Entry) / vcbSpace->blockSize;
		// if(sizeof(Entry) % vcbSpace->blockSize > 0){
		// 	blockCount++;
		// }

		
		// if(buffer == NULL){
		// 	perror("malloc buffer for root directory");
		// 	return errno;
		// }

		// LBAread(buffer, blockCount, vcbSpace->startOfRoot); /////

		// rootDirPointer = malloc()
	}
	else{

			//return the structure of the volume control block in case start of free space
		// if(initVCB(numberOfBlocks, blockSize, vcbPointer) != 0){
		// 	printf("initVCB() failed");
		// 	return -1;
		// }
		// if (initFreespace() != 0) 	// intializing the free space
		// {
		// 	printf("initFreespace() failed");
		// 	return -1;
		// }
		if (initFreeSpace() != 0) 	// intializing the free space
		{
			printf("initFreespace() failed");
			return -1;
		}
		// 	// intializing the root directory 
		// if (initRootDir() != 0)
		// {
		// 	printf("initRootDir() failed");
		// 	return -1;
		// }
		
		//WRITE VCB TO DISK

		vcb->blockSize = blockSize;
		vcb->numberOfBlocks = numberOfBlocks;

		vcb->freeMapAddress = 1;
		vcb->freeLen = (numberOfBlocks + 7) / 8;
		printf ("vcb.freeLen: %hhn \n", vcb->startOfFreeSpace);
		
		vcb->mapBlocks = (vcb->freeLen + blockSize -1) / blockSize;
		printf("vcb.mapBlocks: %u \n", vcb->mapBlocks);
		
		vcb->dirLen = DIR_BLOCKS * blockSize / sizeof(Entry);
		printf("vcb.dirLen: %d \n", vcb->dirLen);
		
		ret = initFreeSpace();
		if (ret != 1){
			printf("ERROR, initFreeSpace()\n");
			return -1;
		}
		vcb->startOfRoot = DIR_BLOCKS;
		if(createDir(0) == NULL){
			printf("ERROR, initRoot()\n");
			return -1;
		}
		vcb->magicNumber = MAGICNUMBER;
		ret = LBAwrite(vcb, 1, 0);
		if(ret != 1) {
			err = errno;
			perror("Writing vcb");
			return err;
		}

		
	}



	vcb->cwd = malloc (vcb->startOfRoot * vcb->blockSize);
	ret = (int) LBAread (vcb->cwd, vcb->startOfRoot, vcb->rootAddress);
	vcb->cwd = malloc(MAX_PATH);
	strncpy(vcb->cwdName, "/", MAX_PATH);
	
	
	return 0;
	
// uint64_t blockSize;
// 	uint64_t numberOfFreeBlocks;
// 	uint64_t startOfFSBlock;
// 	uint64_t startOfFreeSpace;
// 	uint64_t startOfRoot;
}
	
	
void exitFileSystem ()
	{
	printf ("System exiting\n");
	}
