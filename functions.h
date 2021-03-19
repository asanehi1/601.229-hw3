#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>

struct Cache {
    int tag;
    int dirty;
    int accessCount;
    int index;
};

int powerOfTwo(int num);
int load(std::vector<Cache> &cache, int sets, int blocks, int bytes
        , std::string writeAlloc, std::string writeTB, unsigned long address);
int store(std::vector<Cache> &cache, int sets, int blocks, int bytes
        , std::string writeAlloc, std::string writeTB, unsigned long address);
void writeAllocate(std::vector<Cache> &cache);
void writeThrough(/*param*/);
void writeBack(/*param*/);
void lru(std::vector<Cache> &cache);
void fifo(/*param*/);
unsigned long hexToBinary(char s[]);