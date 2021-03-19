#include <cstdio>
#include <iostream>
#include "functions.h"
#include <stdio.h>
#include <vector>

using std::vector;
using std::string;

int main (int argc, char *argv[]) {
    if(argc != 7) {
        printf("ERROR: not enough arguments\n");
        return 1;
    }

    int numSets = atoi(argv[1]);
    int numBlocks = atoi(argv[2]);
    int numBytes = atoi(argv[3]);
    string writeAllocOrNoAlloc = argv[4];
    string writeThroughOrBack = argv[5];
    string lruOrFifo = argv[6];

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
    if(writeAllocOrNoAlloc != "write-allocate" && writeAllocOrNoAlloc != "no-write-allocate") {
        printf("ERROR: Expected write-allocate or no-write-allocate\n");
        return 1;
    }

    //validate it is either "write-through" or "write-back"
    if(writeThroughOrBack != "write-through" && writeThroughOrBack != "write-back") {
        printf("ERROR: Expected write-through or write-back\n");
        return 1;
    }
    
    if(writeAllocOrNoAlloc == "no-write-allocate" && writeThroughOrBack == "write-back") {
        printf("ERROR: Cannot have \"no-write-allocate\" and \"write-back\" together.\n");
        return 1;
    }

    //validate it is either "lru" or "fifo"
    if(lruOrFifo != "lru" && lruOrFifo != "fifo") {
        printf("ERROR: Expected lru or fifo\n");
        return 1;
    }

    
    // add counters somewhere to keep track of values
    // values to keep track of:
    // load, store, load hits, load misses, store hits, store misses, total cycles
    //vector<unsigned long> addresses;
    unsigned long address;
    vector<Cache> cache(numSets * numBlocks);

    int sHits = 0, sMisses = 0;
    int lHits = 0, lMisses = 0;
    int tLoads = 0, tStore = 0, tCycles = 0;

    while (std::cin.peek() != EOF) {
      string firstValue;
      std::cin >> firstValue;
      
      // hex value
      char secondValue[10];
      std::cin >> secondValue;

      // don't use 3rd value for anything 
      string thirdValue;
      std::cin >> thirdValue;

      // this is just a print statement
      std::cout << firstValue << " " << secondValue << " " << thirdValue <<std::endl;
      //address = hexToBinary(secondValue);

        address = hexToBinary(secondValue);
      if (firstValue == "l") {
	    // load hex value (2nd value in set)                                   
        // if load returns 0, it was a hit                                    
        // if load returns 1, it was a miss 
        if(load(cache, numSets, numBlocks, numBytes, writeAllocOrNoAlloc, writeThroughOrBack, address) == 1) {
            lMisses++;
            tCycles +=100;
        } else {
            lHits++;
            tCycles++;
        }
        tLoads++;
      } else if (firstValue == "s") {
        // store hex value (2nd value in set)
        // if store returns 0, it was a hit
	    // if store returns 1, it was a miss  
        // either call write allocate or no write allocate 
        if(store(cache, numSets, numBlocks, numBytes, writeAllocOrNoAlloc, writeThroughOrBack, address) == 1) {
            lMisses++;
            tCycles += 100;
        } else {
            lHits++;
            tCycles++;
        }
        tStore++;
      } else {
	    std::cout << "ERROR: file has neither l or s" << std::endl;
        return 1;
      }
    }

    std::cout << "Total loads: " << tLoads << "\n";
    std::cout << "Total stores: " << tStore << "\n";
    std::cout << "Load hits: " << lHits << "\n";
    std::cout << "Load misses: " << lMisses << "\n";
    std::cout << "Store hits: " << sHits << "\n";
    std::cout << "Store misses: " << sMisses << "\n";
    std::cout << "Total cycles: " << tCycles << "\n";

    return 0;
}
