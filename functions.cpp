#include <cstdlib>
#include <cstring>
#include <iostream>
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <math.h>

using std::vector;
using std::map;
using std::string;

// check for power of two
// return 1 if true
// return 0 if false
int powerOfTwo(int num) {
  if(num != 0 && (num & (num - 1)) == 0 ) {
    return 1;
  }

  return 0;
}

unsigned long hexToBinary(char s[]) {
  unsigned long ul = strtoul(s, NULL, 16);
  std::cout <<"address = "<< ul << "\n";
  unsigned long i = ul;

  std::cout << "\ntag 2 bits: " << (i & (111 << 25)) << "\n";
  return ul;
}


// return 0 if hit (tag exists)                                                                                                           
// return 1 if miss (tag can't be read / found)                                                                                          
// read data 
int load(std::vector<std::vector<std::map<std::string, int>>> &cache, int sets, int blocks
          , int bytes, std::string writeAlloc, std::string writeTB, unsigned long address) {
    
  //need help with these calculations
  int indexBits = log2(sets);
  int offset = log2(blocks);
  int tagBits = 32 - indexBits - offset;

  int tag, index;
  //Get index and tag from address




  return 1;
}



  
// return 0 if hit (store same tag)
// return 1 if miss (tag mismatch)
// write data
int store(std::vector<std::vector<std::map<std::string, int>>> &cache, int sets, int blocks
          , int bytes, std::string writeAlloc, std::string writeTB, unsigned long address) {


  return 1;
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

