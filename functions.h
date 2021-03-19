#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>

int powerOfTwo(int num);
int load(std::vector<std::vector<std::map<std::string, int>>> &cache, int sets
                , int blocks, int bytes, std::string writeAlloc, std::string writeTB
                , unsigned long address);
int store(std::vector<std::vector<std::map<std::string, int>>> &cache, int sets
                , int blocks, int bytes, std::string writeAlloc, std::string writeTB
                , unsigned long address);
void writeAllocate(/*param*/);
void writeThrough(/*param*/);
void writeBack(/*param*/);
void lru(/*param*/);
void fifo(/*param*/);
unsigned long hexToBinary(char s[]);