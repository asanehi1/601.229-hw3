#include <iostream>
#include "functions.h"

// check for power of two
// return 0 if true
// return 1 if false
int powerOfTwo(int num) {
    if(num != 0 && (num & (num - 1)) == 0 ) {
        return 0;
    }

    return 1;
}


// return 0 if hit (tag exists)                                                                                                           
// return 1 if miss (tag can't be read / found)                                                                                          
// read data 
int load(/*param*/) {
}



  
// return 0 if hit (store same tag)
// return 1 if miss (tag mismatch)
// write data
int store(/*param*/) {
  return;
}

// if store miss, either write allocate or no write allocate
// no write allocate doesn't do anything, don't modify cache 

//bring the relevant memory block into the cache before the store proceeds
void writeAllocate(/*param*/) {
  // TODO
  // maybe return if necessary 
}

// write through or write back is affected by writeAllocate and noWriteAllocate

// a store writes to the cache as well as to memory
void writeThrough(/*param*/) {
  // TODO
}

// a store writes to the cache only and marks the block dirty
//if the block is evicted later, it has to be written back to memory before being replaced
void writeBack(/*param*/) {
  // TODO
}


//evicts

//(least-recently-used) we evict the block that has not been accessed the longest
void lru(/*param*/) {
  // evict block
  // TODO
}

//(first-in-first-out) we evict the block that has been in the cache the longest
void fifo(/*param*/) {
  // evict block
  // TODO
}

