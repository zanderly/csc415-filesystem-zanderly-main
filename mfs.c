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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fsLow.h"
#include "mfs.h"
<<<<<<< HEAD
#include "fsInit.c"

dirEnt_t* createDir(uint64_t parentAddr) {
=======


Entry* createDir(uint64_t parentAddr) {
>>>>>>> Beta
    // Request blocks, return NULL if allocBlocks fails
    uint64_t dirLoc = allocBlocks(DIR_BLOCKS);
//    printf("createDir: dirLoc = %lu\n", dirLoc);
    if(dirLoc == 0) {
        freeBlocks(parentAddr, DIR_BLOCKS);
        return NULL;
    }
   // printf("in createDir: dirLoc = %ld\n", dirLoc);
<<<<<<< HEAD
    dirEnt_t* dir = malloc(sizeof(*dir) * vcb->dirLen);
=======
    Entry* dir = malloc(sizeof(*dir) * vcb->dirLen);
>>>>>>> Beta
    if(dir == NULL) {
        err = errno;
        perror("createDir");
        freeBlocks(parentAddr, DIR_BLOCKS);
        return NULL;
    }
}
<<<<<<< HEAD
bool parsePath(char *path, unsigned char condition, DE *tempWorkingDir, char *token)
{
    
    if (path[0] != '/')
    {
      
        int mallocSize = sizeof(DE) * mfs_defaultDECount;
        int numOfBlockNeeded = (mallocSize / mfs_blockSize) + 1;
        LBAread(tempWorkingDir, numOfBlockNeeded, mfs_cwd_location);
    }
    else
    {
        LBAread(tempWorkingDir, mfs_vcb->rootSize / mfs_blockSize, mfs_vcb->rootLocation);
=======

bool parsePath(char *path, unsigned char condition, DE *tempDir, char *token){

    
    if (path[0] != '/')
    {
        int blockNeedCount = ((sizeof(DE) * DIRECTORY_ENTRIES) / vcb.blockSize) + 1;
        LBAread(tempDir, blockNeedCount, mfs_cwd_location);
    }
    else
    {
        LBAread(tempDir, mfs_vcb->rootSize / vcb.blockSize, mfs_vcb->rootLocation);
>>>>>>> Beta
    }

    int tokenCount = 0;
    char **tokens = malloc((strlen(path) / 2) * sizeof(char *)); 
    char *theRest;
    char *token = strtok_r(path, "/", &theRest);

  
    while (token != NULL)
    {
        
        tokens[tokenCount] = token;
       
        tokenCount++;
        token = strtok_r(NULL, "/", &theRest);
    }
    
    bool found = 0;
    for (int tokIndex = 0; tokIndex < tokenCount - 1; tokIndex++)
    {
       
<<<<<<< HEAD
        for (int dirIndex = 0; dirIndex < mfs_defaultDECount; dirIndex++)
        {
            if (strcmp(tempWorkingDir[dirIndex].name, tokens[tokIndex]) == 0)
            {
                
                found = 1;
                int blockCount = tempWorkingDir[dirIndex].size / mfs_blockSize;
                int ret = LBAread(tempWorkingDir, blockCount, tempWorkingDir[dirIndex].location);
=======
        for (int dirIndex = 0; dirIndex < DIRECTORY_ENTRIES; dirIndex++)
        {
            if (strcmp(tempDir[dirIndex].name, tokens[tokIndex]) == 0)
            {
                
                found = 1;
                int blockCount = tempDir[dirIndex].size / vcb.blockSize;
                int ret = LBAread(tempDir, blockCount, tempDir[dirIndex].location);
>>>>>>> Beta
                if (ret != blockCount)
                {
                    printf("Error, reading failed", ret, blockCount);
                    free(tokens);
                    tokens = NULL;
                    return 0;
                }
                break;
            }
        }
        if (!found)
        {
            
            printf("Error, the directory does not exist \n");
            free(tokens);
            tokens = NULL;
            return 0;
        }
        found = 0;
    }

   
    unsigned char thisCondition = NOT_EXIST;
    if (tokenCount != 0)
    {
        strcpy(token, tokens[tokenCount - 1]);
    }
<<<<<<< HEAD
    for (int i = 0; i < mfs_defaultDECount; i++)
    {
        if (strcmp(tempWorkingDir[i].name, token) == 0)
        {
            thisCondition = EXIST;
            if (tempWorkingDir[i].isDir)
=======
    for (int i = 0; i < DIRECTORY_ENTRIES; i++)
    {
        if (strcmp(tempDir[i].name, token) == 0)
        {
            thisCondition = EXIST;
            if (tempDir[i].isDir)
>>>>>>> Beta
            {
                thisCondition = EXIST_DIR;
            }
            else
            {
             
                thisCondition = EXIST_FILE;
            }
            break;
        }
    }

    if (strcmp(path, "/") == 0)
    {
        
        thisCondition = EXIST_DIR;
    }

  

    free(tokens);
    tokens = NULL;

    if (condition == (EXIST_FILE | EXIST_DIR))
    {
      
        if (thisCondition != NOT_EXIST)
        {
            
            return 1;
        }
    }

    if ((condition) == thisCondition)
    {
        return 1;
    }
    return 0;
}

<<<<<<< HEAD
 int fs_opendir(const char *pathname){
	char path[strlen(name)];
    	strcpy(path, name);
    
    	int mallocSize = sizeof(DE) * mfs_defaultDECount;
   	int numOfBlockNeeded = (mallocSize / mfs_blockSize) + 1;
    	mallocSize = numOfBlockNeeded * mfs_blockSize;
    	DE *tempWorkingDir = malloc(mallocSize);
    	char *token = malloc(256);
=======
int fs_opendir(const char *pathname){
	char path[strlen(name)];
    strcpy(path, name);
    
    int mallocSize = sizeof(DE) * mfs_defaultDECount;
   	int numOfBlockNeeded = (mallocSize / mfs_blockSize) + 1;
    mallocSize = numOfBlockNeeded * mfs_blockSize;
    DE *tempWorkingDir = malloc(mallocSize);
    char *token = malloc(256);
>>>>>>> Beta

    bool valid = pathParser(path, EXIST_DIR, tempWorkingDir, token);
    if (!valid)
    {
<<<<<<< HEAD
        printf("[ERROR] Dir.c line 419: invalid path\n");
=======
        printf("error, uable to open directory\n");
>>>>>>> Beta
        return NULL;
    }

    int DEindex;
    for (int i = 2; i < mfs_defaultDECount; i++)
    {
        if (strcmp(tempWorkingDir[i].name, token) == 0)
        {
   	    DEindex = i;
            break;
        }
    }
    if (strcmp(token, "\0") == 0)
    {
        DEindex = 0;
    }

    int *dirp = malloc(sizeof(dirp));

    dirp->d_reclen = tempWorkingDir[DEindex].size;
    dirp->directoryStartLocation = tempWorkingDir[DEindex].location;
    dirp->dirEntryPosition = DEindex;
    strcpy(dirp->d_name, tempWorkingDir[DEindex].name);
    if (tempWorkingDir[DEindex].isDir)
    {
        dirp->fileType = DT_DIR;
    }
    else
    {
        dirp->fileType = DT_REG;
    }

    free(tempWorkingDir);
    tempWorkingDir = NULL;
    free(token);
    token = NULL;
    return dirp;
}

<<<<<<< HEAD
int fs_isFile(char * filename){
    struct Entry file = (Entry*)malloc(sizeof(Entry));
    if(file->id == filename){
       return 1;
    }else{
       return 0;
    }
}



struct fs_diriteminfo *fs_readdir(fdDir *dirp){
    for(int i = dirp->dirEntryPosition; i < DIRECTORY_ENTRIES; i++){
=======
int fs_closedir(fdDir *dirp)
{
    if (dirp == NULL)
    {
        printf("error, close dir faild.. /n");
        return -1;
    }

    free(dirp);
    dirp = NULL;

    return 1;
}

int fs_isFile(char * filename){
    Entry *cwdCopy = cwd;

    int isOpen = 0;
    //Checks if directory is open
    if (dirOpen != NULL){
        isOpen = 1;
        cwd = dirOpen;
    }
    int result = 0;

    //Check if Item is in directory
    //return 1;

    if(isOpen){ //begin reset
        cwd = cwdCopy;
    }

    free(getSize)
    return result; //return 1 if is file, 0 if not  
}

struct fs_diriteminfo *fs_readdir(fdDir *dirp){
    for(int i = dirp->dirEntryPosition; i < DIRECTORY_ENTRIES; i++){
        //get the first entry and mark the index of it
>>>>>>> Beta
         if(){
           strcpy(dirp->dirPointer->diriteminfo.d_name, dirp->);
           dirp->dirPointer->diriteminfo.fileType = Typeof();
           dirp->dirEntryPosition = i+1;
           return (dirp-dirPointer-diriteminfo);
         }
    }
<<<<<<< HEAD
    return NULL;
}

int fs_setcwd(char *buf)
{
    char path[strlen(buf)];
    strcpy(path, buf);
=======
    //return NULL/reset if no more entries in dir
    return NULL;
}

char *fs_getcwd(char *buf, size_t size)
{

    char **tokenArray = malloc(size);
    if(tokenArray == NULL){
        err = errno;
        perror("Error in buffer");
		return err;
    }
    int tokenCount = 0;
    int findNameOf = 0;
>>>>>>> Beta
    int mallocSize = sizeof(DE) * mfs_defaultDECount;
    int numOfBlockNeeded = (mallocSize / mfs_blockSize) + 1;
    mallocSize = numOfBlockNeeded * mfs_blockSize;
    DE *tempWorkingDir = malloc(mallocSize);
<<<<<<< HEAD
    char *token = malloc(256);
    bool valid = parsePath(path, EXIST_DIR, tempWorkingDir, token);
=======
    LBAread(tempWorkingDir, numOfBlockNeeded, mfs_cwd_location);
    findNameOf = tempWorkingDir[0].location;
   
    while (tempWorkingDir[1].location != tempWorkingDir[0].location)
    {
        LBAread(tempWorkingDir, numOfBlockNeeded, tempWorkingDir[1].location); //"foo"
       
        for (int i = 2; i < mfs_defaultDECount; i++)
        {
            if (tempWorkingDir[i].location == findNameOf)
            {
         
                tokenArray[tokenCount] = malloc(sizeof(tokenArray) * strlen(tempWorkingDir[i].name) +1);
           
                strcpy(tokenArray[tokenCount], tempWorkingDir[i].name);
               
                tokenCount++;
                break;
            }
        }
        findNameOf = tempWorkingDir[0].location;
    }

    char *path = malloc(size + tokenCount - 1);
   
    strcpy(path, "/"); 
    for (int i = tokenCount - 1; i >= 0; i--)
    {
      
        strcat(path, tokenArray[i]); 
        if (i > 0)
            strcat(path, "/");
       
    }

    strcpy(buf, path);

    free(tempWorkingDir);
    free(tokenArray);
    tempWorkingDir = NULL;
    tokenArray = NULL;

    return path;
}

int fs_setcwd(char *buf){


    char path[strlen(buf)];
    strcpy(path, buf);

    char *token = malloc(256);
    int blockNeedCount = ((sizeof(DE) * DIRECTORY_ENTRIES) / vcb.blockSize) + 1;
    int mallocSize = blockNeedCount * vcb.blockSize;

    DE *tempDir = malloc(mallocSize);
    
    bool valid = parsePath(path, EXIST_DIR, tempDir, token);
    
>>>>>>> Beta
    if (!valid)
    {
        printf("Error, Invalid Path..\n");
        return -1;
    }
<<<<<<< HEAD
    for (int i = 0; i < mfs_defaultDECount; i++)
    {
        if (strcmp(tempWorkingDir[i].name, token) == 0)
        {
            mfs_cwd_location = tempWorkingDir[i].location;
=======
    for (int i = 0; i < DIRECTORY_ENTRIES; i++)
    {
        if (strcmp(tempDir[i].name, token) == 0)
        {
            mfs_cwd_location = tempDir[i].location;
>>>>>>> Beta
            break;
        }
    }
}
<<<<<<< HEAD
int deleteDirEnt(dirEnt_t* parent, int index) {
=======

int deleteDirEnt(dirEnt_t* parent, int index) {

>>>>>>> Beta
    uint64_t address = parent[index].location;

    parent[index].dateTimeCr = 0;
    parent[index].dateTimeMd = 0;
    parent[index].location = 0;
    parent[index].size = 0;
    parent[index].attr = 0;
<<<<<<< HEAD
=======
    
>>>>>>> Beta
    strncpy(parent[index].name, "", strlen(parent[index].name));

    freeBlocks(address, DIR_BLOCKS);

    LBAwrite(parent, DIR_BLOCKS, parent[0].location);

    return 1;
}

<<<<<<< HEAD
int fs_stat(const char *path, struct fs_stat *buffer)
{
=======
int fs_stat(const char *path, struct fs_stat *buffer){
>>>>>>> Beta

    char convertedPath[strlen(path)];
    strcpy(convertedPath, path);

<<<<<<< HEAD
=======

>>>>>>> Beta
    int mallocSize = sizeof(DE) * mfs_defaultDECount;
    mallocSize = numOfBlockNeeded * mfs_blockSize;
    DE *tempWorkingDir = malloc(mallocSize);
    char *token = malloc(256);
    bool valid = pathParser(convertedPath, EXIST_DIR | EXIST_FILE, tempWorkingDir, token);
    int numOfBlockNeeded = (mallocSize / mfs_blockSize) + 1;

<<<<<<< HEAD
    if (!valid)
=======
    int blockNeedCount = ((sizeof(DE) * DIRECTORY_ENTRIES) / vcb.blockSize) + 1;
    char *token = malloc(256);

    DE *tempDir = malloc(blockNeedCount * vcb.blockSize);

    if (!pathParser(convertedPath, EXIST_DIR | EXIST_FILE, tempDir, token))
>>>>>>> Beta
    {
        printf("Error, invalid path \n");
        return -1;
    }
<<<<<<< HEAD

    
    int directoryEntryIndex;
    for (int i = 2; i < mfs_defaultDECount; i++)
    {
        if (strcmp(token, tempWorkingDir[i].name) == 0)
=======
    
    int directoryEntryIndex;
    for (int i = 2; i < DIRECTORY_ENTRIES; i++)
    {
        if (strcmp(token, tempDir[i].name) == 0)
>>>>>>> Beta
        {
            directoryEntryIndex = i;
            break;
        }
    }

<<<<<<< HEAD
    buffer->st_size = tempWorkingDir[directoryEntryIndex].size;
    buffer->st_blksize = mfs_blockSize;
    buffer->st_blocks = numOfBlockNeeded;
    buffer->st_createtime = tempWorkingDir[directoryEntryIndex].createTime;
    buffer->st_modtime = tempWorkingDir[directoryEntryIndex].lastModTime;
    buffer->st_accesstime = tempWorkingDir[directoryEntryIndex].lastAccessTime;

    free(tempWorkingDir);
    tempWorkingDir = NULL;
=======
    buffer->st_size = tempDir[directoryEntryIndex].size;
    buffer->st_blksize = vcb.blockSize;
    buffer->st_blocks = blockNeedCount;
    buffer->st_createtime = tempDir[directoryEntryIndex].createTime;
    buffer->st_modtime = tempDir[directoryEntryIndex].lastModTime;
    buffer->st_accesstime = tempDir[directoryEntryIndex].lastAccessTime;

    free(tempDir);
    tempDir = NULL;
>>>>>>> Beta
    free(token);
    token = NULL;

    return 1;
}

int isDirEmpty(dirEnt_t* dir) {
    int ret = 1;
    for(int i = 2; i < vcb->dirLen; i++) {
        if(dir[i].size != 0) {
            ret = 0;
        } 
    }

    return ret;
}

<<<<<<< HEAD
=======
int fs_delete(char *filename)
{
    char path[strlen(filename)];
    strcpy(path, filename);
   
    int mallocSize = sizeof(DE) * mfs_defaultDECount;
    int numOfBlockNeeded = (mallocSize / mfs_blockSize) + 1;
    mallocSize = numOfBlockNeeded * mfs_blockSize;
    DE *tempWorkingDir = malloc(mallocSize);
    char *lastToken = malloc(256);

    bool valid = pathParser(path, EXIST_DIR | EXIST_FILE, tempWorkingDir, lastToken);
   
    if (!valid)
    {
        printf("Error, Invalid path.. \n");
        return -1;
    }

    int DEindex = -1;
    for (int i = 2; i < mfs_defaultDECount; i++)
    {
     
        if (strcmp(tempWorkingDir[i].name, lastToken) == 0)
        {
            DEindex = i;
            break;
        }
    }

    int release_ret = releaseFreeSpace(tempWorkingDir[DEindex].location, tempWorkingDir[DEindex].size / mfs_blockSize);
    if (release_ret == -1)
    {
        printf("Error, Release free space faild... \n");
        return -1;
    }

 
    strcpy(tempWorkingDir[DEindex].name, "\0");
    tempWorkingDir[DEindex].location = 0;
    tempWorkingDir[DEindex].size = 0;
    tempWorkingDir[DEindex].isDir = 0;
    tempWorkingDir[DEindex].createTime = 0;
    tempWorkingDir[DEindex].lastModTime = 0;
    tempWorkingDir[DEindex].lastAccessTime = 0;
    int lba_ret = LBAwrite(tempWorkingDir, tempWorkingDir[0].size / mfs_blockSize,   tempWorkingDir[0].location);
    if (lba_ret != tempWorkingDir[0].size / mfs_blockSize)
    {
        printf("[ERROR] fsDir.c line 410: LBAwrite failed...\n");
        return -1;
    }

    return 1;
}

>>>>>>> Beta
int fs_rmdir(char* pathname) {
    struct pathInfo info;
    int ret = 0;

<<<<<<< HEAD
=======
    char *path = malloc(strlen(pathname) + 1);
    if(path == NULL){
        perror("Couldnt find directory path");
		return errno;
    }
    strcpy(path, pathname);

    
>>>>>>> Beta
    if(parsePath(&info, pathname) == 0) {
        dirEnt_t* dir = malloc(DIR_BLOCKS * vcb->blockSize);
        loadDir(dir, info.parent[info.index].location);

        if(isDirEmpty(dir)) {
            deleteDirEnt(info.parent, info.index);
            ret = 1;
        }
    }

    if(info.parent) {
        if(info.parent != vcb->cwd && info.parent != vcb->root) {
            free(info.parent);
        }
    }

<<<<<<< HEAD
=======
    free(path);
>>>>>>> Beta
    return ret;
}

int fs_isDir(char *path){
<<<<<<< HEAD

    char path_arr[strlen(path) + 1];
    strcpy(path_arr, path);

    int mallocSize = sizeof(DE) * mfs_defaultDECount;
    mallocSize = numOfBlockNeeded * mfs_blockSize;
    DE *tempWorkingDir = malloc(mallocSize);
    char *lastToken = malloc(256);
    int numOfBlockNeeded = (mallocSize / mfs_blockSize) + 1;

    //find out if valid

    return 1; //return 0 or 1, but not implemented yet
}

int fs_mkdir(const char *pathname, mode_t mode){
=======
    Entry *cwdCopy = cwd;

    //Checks if directory is open
    if (dirOpen != NULL){
        cwd = dirOpen;
    }
    int result = 0;

    Entry *getSize = malloc(sizeof(Entry));

    if(getSize != NULL){
        result = 1;
    }

    free(getSize)
    return result; //return 1 if exists, 0 if not
}

int fs_mkdir(const char *pathname, mode_t mode){

>>>>>>> Beta
    char *path = malloc(strlen(pathname) + 1);

    if(path == NULL){
        printf("Unable to malloc space for path.");
        return -1;
    }
    strcpy(path, pathname);

<<<<<<< HEAD
=======
    if(parent->)
>>>>>>> Beta
    //malloc space needed
    //check dir name
    //get directory pointer?>
    //create directory
    //cleanup

    return 1;
}
<<<<<<< HEAD
=======

char * fs_getcwd(char *buf, size_t size){
    strcpy(buf, "");

    char *cwd = malloc(sizeof(char) * (size + 1));
    strcpy(cwd, fs_Dir.cwd);
     
    //Make copy of directory
    //loop until we find absolute path
    //Iff path name is : current directory, includes the terminating null byte
    //exceeds size byte -> return NULL
    return cwd;
}

int fs_isFile(char * path){

    
    char path_arr[strlen(path) + 1];
    strcpy(path_arr, path);

    int blockNeedCount = ((sizeof(DE) * DIRECTORY_ENTRIES) / vcb.blockSize) + 1;
    char *lastToken = malloc(256);

    DE *tempDir = malloc(blockNeedCount * vcb.blockSize);
    
    //check if it is valid file

    // return bool value

    return 1;

}

fdDir * fs_opendir(const char *name){

    char path_arr[strlen(name)];
    strcpy(path_arr, name);

    int blockNeedCount = ((sizeof(DE) * DIRECTORY_ENTRIES) / vcb->blockSize) + 1;
    char *lastToken = malloc(256);

    DE *tempDir = malloc(blockNeedCount * vcb.blockSize);
    
    //check if valid path

    //cleanup

    //return a pointer to the directory stream
    return 0;

}

struct fs_diriteminfo *fs_readdir(fdDir *dirp){

    //for each entry in directory
    
    for(i = dirp->dirEntryPosition; i < DIRECTORY_ENTRIES;i++){
       if(dirp->dArray[i]){
         strcpy(dirp->infoStruct.d_name, dirp->dArray[i].name);
         dirp->infoStruct.fileType = Typeof(dirp->dArray[i]);
         dirp->dirEntryPosition = i+1;
         return dirp->infoStruct;
       }
    }
    
    //returns pointer

    //returns null on reaching end of directory stream

    return NULL;
}

int fs_closedir(fdDir *dirp){

    if(dirp == NULL){ //argument check if invalid
        printf("Error, check argument to close file.");
        return -1;
    }
    else{ //no error in argument, proceed
        free(dirp);
        dirp = NULL;
        return 0;
        //return 1;
    }

}
>>>>>>> Beta
