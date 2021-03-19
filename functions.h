#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>

struct Cache {
    long tag;
    int dirty;
    int accessCount;
    long index;
};

int powerOfTwo(int num);
int load(std::vector<Cache> &cache, int sets, int blocks, int bytes
        , std::string writeAlloc, std::string writeTB, unsigned long address);
int store(std::vector<Cache> &cache, int sets, int blocks, int bytes
        , std::string writeAlloc, std::string writeTB, unsigned long address);
void writeAllocate(std::vector<Cache> &cache);
void writeThrough(/*param*/);
void writeBack(/*param*/);
void lru(/*param*/);
void fifo(/*param*/);
unsigned long hexToBinary(std::string s);
int checkAddressInCache(Cache &c, std::vector<Cache>&cache, int blocks);
