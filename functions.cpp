
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

int addAddressToCache(Cache &c, vector<Cache>&cache, int &blocks, string &lruOrFifo, int &time) {
  //check if theres an empty spot in the set
  int startIndex = c.index *(blocks);
  for (int i = startIndex; i < startIndex + blocks; i++) {
    if(cache.at(i).index == -1) {
      cache.at(i) = c;
      cache.at(i).accessCount++;
      cache.at(i).timestamp = time;
   
      return 0;
    }
  }

  //There is no empty spot so do an evict
  if (lruOrFifo == "fifo") {
    fifo(cache, startIndex, startIndex + blocks, c, time);
  } else {
    lru(cache, startIndex, startIndex + blocks, c);
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
      return 0;
    }
  }

  return 1;
}


// return 0 if hit (tag exists)                                                                                                           
// return 1 if miss (tag can't be read / found)                                                                                          
// read data 
int load(vector<Cache> &cache, int &sets, int &blocks, int &bytes
	,string &writeAlloc, string &writeTB, unsigned long &address, string &fifoOrLru, int &time) {

  long tag, index = 0;
  getTagIndex(sets, blocks, bytes, address, index, tag);
  Cache c = {.tag = tag,.dirty = 0,.accessCount = 1,.index = index, .timestamp = 1};
  
  if(checkAddressInCache(c, cache, blocks) == 0) {
    return 0;
  }

  addAddressToCache(c, cache, blocks, fifoOrLru, time);

  return 1;
}

int store(vector<Cache> &cache, int &sets, int &blocks, int &bytes
	,string &writeAlloc, string &writeTB, unsigned long &address, string &fifoOrLru, int &time) {

  long tag, index = 0;
  getTagIndex(sets, blocks, bytes, address, index, tag);
  Cache c = {.tag = tag,.dirty = 0,.accessCount = 1,.index = index, .timestamp = time};
  
  if(writeAlloc == "write-allocate" && writeTB == "write-through") {
    //checks if address is in cache
    if(checkAddressInCache(c, cache, blocks) == 0) {
      return 0;
    } 

    //its not so add the address to cache
    addAddressToCache(c, cache, blocks, fifoOrLru, time);

  } else if(writeAlloc == "write-allocate" && writeTB == "write-back") {
    //check if address is in the cache
    if(checkAddressInCache(c, cache, blocks) == 0) {
      cache.at(c.index/* *(blocks)*/).dirty = 1;
      return 0;
    } 

    //its not add it and mark it as dirty
    addAddressToCache(c, cache, blocks, fifoOrLru, time);
    cache.at(c.index).dirty = 1;
    cache.at(c.index).accessCount++;
   
    
  } else if(writeAlloc == "no-write-allocate" && writeTB == "write-through") {
    if(checkAddressInCache(c, cache, blocks) == 0) {
      return 0;
    } 

  }

  return 1;
}

//evicts
//(least-recently-used) we evict the block that has not been accessed the longest
void lru(vector<Cache> &cache, int startIndex, int endIndex, Cache &c) {
  int index = startIndex + 1;
  int count = cache.at(startIndex + 1).accessCount;

  //go through each slot in set and check
  //which one was accessed the least recent
  for(int i = startIndex + 1; i <= endIndex; i++) {
    if(count > cache.at(i).accessCount) {
      index = i;
      count = cache.at(i).accessCount;
    }
  }

  //replace that address with the new address
  cache.at(index) = c;
  cache.at(index).accessCount++;
}


//(first-in-first-out) we evict the block that has been in the cache the longest
void fifo(vector<Cache> &cache, int startIndex, int endIndex, Cache &c, int &time) {
  int index = startIndex + 1;
  int count = cache.at(startIndex + 1).timestamp;

  //go through each slot in set and check
  //which one was added the oldest
  for(int i = startIndex + 1; i <= endIndex; i++) {
    if(count > cache.at(i).timestamp) {
      index = i;
      count = cache.at(i).timestamp;
    }
  }

  //replace that address with the new address
  cache.at(index) = c;
  cache.at(index).timestamp = time;
}

