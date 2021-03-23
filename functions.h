#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>

struct Cache {
    long tag;
    int dirty;
    int accessCount;
    long index;
  //  int timestamp;
  
};

int powerOfTwo(int num);
int loadAndStore(std::vector<Cache> &cache, int sets, int blocks, int bytes
		 , std::string writeAlloc, std::string writeTB, unsigned long address/*, std::string fifoOrLru*/);
void lru(std::vector<Cache> &cache, int startIndex, int endIndex, Cache c);
void fifo(std::vector<Cache> &cache, int startIndex, int endIndex, Cache c);
unsigned long hexToBinary(std::string s);
int checkAddressInCache(Cache &c, std::vector<Cache>&cache, int blocks);
int addAddressToCache(Cache &c, std::vector<Cache>&cache, int blocks /*, std::string fifoOrLru */);
