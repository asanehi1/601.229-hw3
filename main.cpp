#include <cstdio>
#include <iostream>
#include "functions.h"
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[]) {
    if(argc != 7) {
        printf("ERROR: not enough arguments\n");
        return 1;
    }

    int numSets = atoi(argv[1]);
    int numBlocks = atoi(argv[2]);
    int numBytes = atoi(argv[3]);
    std::string writeAllocOrNoAlloc = argv[4];
    std::string writeThroughOrBack = argv[5];
    std::string lruOrFifo = argv[6];

    //validate the number of sets in the cache
    if(numSets <= 0 || powerOfTwo(numSets) == 0) {
        printf("ERROR: Number of set must be a positive power of two\n");
        return 1;
    }

    //validate the number of blocks in each set
    if(numBlocks <= 0 || powerOfTwo(numBlocks) == 0) {
        printf("ERROR: Number of blocks must be a positive power of two\n");
        return 1;
    }

    //validate the number of bytes in each block
    if(numBytes < 4 || powerOfTwo(numBytes) == 0) {
        printf("ERROR: Number of bytes must be a positive power of two and at least 4\n");
        return 1;
    }

    //validate that it is either "write-allocate" or "no-write-allocate"
    if(writeAllocOrNoAlloc == "write-allocate") {

    } else if(writeAllocOrNoAlloc == "no-write-allocate") {

    } else {
        printf("ERROR: Expected write-allocate or no-write-allocate\n");
        return 1;
    }

    //validate it is either "write-through" or "write-back"
    if(writeThroughOrBack == "write-through") {

    } else if(writeThroughOrBack == "write-back") {

    } else {
        printf("ERROR: Expected write-through or write-back\n");
        return 1;
    }

    //validate it is either "lru" or "fifo"
    if(lruOrFifo == "lru") {

    } else if(lruOrFifo == "fifo") {

    } else {
        printf("ERROR: Expected lru or fifo\n");
        return 1;
    }

    //start reading file
    //add counters somewhere to keep track of values
    // values to keep track of:
    // load, store, load hits, load misses, store hits, store misses, total cycles
    for (int i = 0; i <= numSets; i++) {
      // if first char is l
         // load hex value (2nd value in set)
         // if load returns 0, it was a hit
         // if load returns 1, it was a miss
      // if first char is s
         // store hex value (2nd value in set)
         // if store returns 0, it was a hit
	 // if store returns 1, it was a miss  
              // either call write allocate or no write allocate 
      
    }
    return 0;
}
