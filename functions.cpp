
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>



using std::vector;
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

unsigned long hexToBinary(std::string &s) {
  const char * c = s.c_str();
  return strtoul(c, NULL, 16);

}

void getTagIndex(int sets, int blocks, int bytes, unsigned long address
                ,long &index, long &tag) {
  int indexBits = log2(sets);
  int offset = log2(blocks);
  int tagBits = 32 - indexBits - offset;

  //Get index and tag from address                                                                    
  int addressLength = log2(address) + 1;
  if (addressLength < 32 && addressLength > offset + indexBits) {
    tag = address >> (offset + indexBits);
    index = tag << (offset + indexBits);
    index = address ^ index;
    index = index >> (offset);
  } else if (addressLength < 32 && addressLength > offset) {
    tag = 0;
    index = index >> (offset);
  } else if (addressLength == 32) {
    //if addressLength = 32                                                                              
    tag = address >> (32 - tagBits);
    index = tag << (32 - tagBits);
    index = address ^ index;
    index = index >> (offset);
  } else {
    //addressLength <= offset                                                                            
    tag = 0;
    index = 0;
  }
  //std::cout << "tagBits:" << tagBits << " indexBits:" << indexBits << std::endl;
  //std::cout << "tag:" << tag << " index:" << index << std::endl;

}

int addAddressToCache(Cache &c, vector<Cache>&cache, int blocks, int bytes,  string &lruOrFifo, int &tCycles) {
  //check if theres an empty spot in the set
  int startIndex = c.index *(blocks);
  for (int i = startIndex; i < startIndex + blocks; i++) {
    if(cache.at(i).index == -1) {
      cache.at(i) = c;
      cache.at(i).accessCount++;
      cache.at(i).timestamp = tCycles;
      if (c.dirty == 1) {
	//std::cout << "dirt" << std::endl;
        cache.at(i).dirty = 1;
      }
      return 0;
    }
  }

  //There is no empty spot so do an evict
  if (lruOrFifo == "fifo") {
    //std::cout << "fifo" << std::endl;
    if (fifo(cache, startIndex, startIndex + blocks, c, tCycles) == 0) {
      // dirty block was evicted
      // std::cout << "dirty block evicted" << std::endl;  
      tCycles += 25 * bytes;
    }
  } else {
    if(lru(cache, startIndex, startIndex + blocks, c) == 0) {
      //dirty block was evicted
      tCycles += 25 * bytes;
    }
   }
  return 1;
}

//return 0 if theres a hit
//return 1 if theres a miss
int checkAddressInCache(Cache &c, vector<Cache>&cache, int &blocks) {
  int startIndex = c.index *(blocks);

  //check set to see if address is in cache
  for (size_t i = startIndex; i < startIndex + blocks; i++) {
    //c.timestamp += cache.at(i).timestamp; 
    if(cache.at(i).tag == c.tag) {      
      cache.at(i).accessCount++;
      if (c.dirty == 1) {
	//std::cout << "dirt" << std::endl;
	cache.at(i).dirty = 1;
      }
      return 0;
    }
  }

  return 1;
}


// return 0 if hit (tag exists)
// return 1 if miss (tag can't be read / found)                                             
// read data 
int load(vector<Cache> &cache, int &sets, int &blocks, int &bytes
	,string &writeAlloc, string &writeTB, unsigned long &address, string &fifoOrLru, int &tCycles) {

  long tag, index = 0;
  getTagIndex(sets, blocks, bytes, address, index, tag);
  Cache c = {.tag = tag,.dirty = 0,.accessCount = 1,.index = index, .timestamp = tCycles};
  
  if(checkAddressInCache(c, cache, blocks) == 0) {
    return 0;
  }
  
  addAddressToCache(c, cache, blocks, bytes, fifoOrLru, tCycles);
  return 1;
}

// return 0 if hit (tag exists)                                                                   // return 1 if miss (tag can't be read / found)                                                   // read data  
int store(vector<Cache> &cache, int &sets, int &blocks, int &bytes
	,string &writeAlloc, string &writeTB, unsigned long &address, string &fifoOrLru, int &tCycles) {

  long tag, index = 0;
  getTagIndex(sets, blocks, bytes, address, index, tag);
  Cache c = {.tag = tag,.dirty = 0,.accessCount = 1,.index = index, .timestamp = tCycles};
  
  if(writeAlloc == "write-allocate" && writeTB == "write-through") {
    //checks if address is in cache
    if(checkAddressInCache(c, cache, blocks) == 0) {
      return 0;
    } 

    //its not so add the address to cache
    addAddressToCache(c, cache, blocks, bytes, fifoOrLru, tCycles);

  } else if(writeAlloc == "write-allocate" && writeTB == "write-back") {
    c.dirty = 1;
    //check if address is in the cache
    if(checkAddressInCache(c, cache, blocks) == 0) {
      return 0;
    } 

    // address in cache but not "memory"
    addAddressToCache(c, cache, blocks, bytes, fifoOrLru, tCycles);
    
   
    
  } else if(writeAlloc == "no-write-allocate" && writeTB == "write-through") {
    if(checkAddressInCache(c, cache, blocks) == 0) {
      return 0;
    }
    

  }

  return 1;
}

// dirty update just cache
// cache is correct value, not memory
// when u evict block, memory is wrong, so take values in cache and write back to memory (this increase tCycles), then throw away block, then overwrite
// tCycles = 25 * numBytes;



//evicts
//(least-recently-used) we evict the block that has not been accessed the longest
// return 0 if dirty block                                                                      
// return 1 else  
int lru(vector<Cache> &cache, int startIndex, int endIndex, Cache &c) {
  int index = startIndex + 1;
  int count = cache.at(startIndex + 1).accessCount;

  //std::cout << "got to lru" << std::endl;
  //go through each slot in set and check
  //which one was accessed the least recent
  for(int i = startIndex + 1; i <= endIndex; i++) {
    if(count > cache.at(i).accessCount) {
      index = i;
      count = cache.at(i).accessCount;
    }
  }
  if (cache.at(index).dirty == 1) {
    cache.at(index).dirty = 0;
    cache.at(index) = c;
    cache.at(index).accessCount++;
    return 0;
  }
  
  //replace that address with the new address
  cache.at(index) = c;
  cache.at(index).accessCount++;
  return 1;
}


//(first-in-first-out) we evict the block that has been in the cache the longest
// return 0 if dirty block
// return 1 else 
int fifo(vector<Cache> &cache, int startIndex, int endIndex, Cache &c, int &tCycles) {
  int index = startIndex + 1;
  int count = cache.at(startIndex + 1).timestamp;

  // std::cout << "got to fifo" << std::endl;
  //go through each slot in set and check
  //which one was added the longest (so smallest timestamp)
  for(int i = startIndex + 1; i <= endIndex; i++) {
    if(count > cache.at(i).timestamp) {
      index = i;
      count = cache.at(i).timestamp;
    }
  }

  if (cache.at(index).dirty == 1) {
    cache.at(index).dirty = 0;
    cache.at(index) = c;
    cache.at(index).timestamp = tCycles;
    return 0;
  }
  //replace that address with the new address
  cache.at(index) = c;
  cache.at(index).timestamp = tCycles;
  return 1;
}

