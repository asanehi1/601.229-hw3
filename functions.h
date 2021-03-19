#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>

// struct Cache {
//     int tag;
//     int dirty;
//     int accessCount;
//     int index;
// } Caches;

int powerOfTwo(int num);
int load(std::vector<std::vector<std::map<int, int>>> &cache, int sets
                , int blocks, int bytes, std::string writeAlloc, std::string writeTB
                , unsigned long address);
int store(std::vector<std::vector<std::map<int, int>>> &cache, int sets
                , int blocks, int bytes, std::string writeAlloc, std::string writeTB
                , unsigned long address);
void writeAllocate(std::vector<std::vector<std::map<int, int>>> &cache);
void writeThrough(/*param*/);
void writeBack(/*param*/);
void lru(/*param*/);
void fifo(/*param*/);
unsigned long hexToBinary(char s[]);