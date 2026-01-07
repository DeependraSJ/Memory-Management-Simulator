#ifndef physicalMemory_h
#define physicalMemory_h
#include <cstddef>
#include <vector>
#include "memoryBlock.h"
using namespace std;

class physicalMemory 
{
    private:
    size_t ttlsz;
    vector<char> memory;      
    memoryBlock* head;            
    public:
    physicalMemory(size_t sz);
    ~physicalMemory(); memoryBlock* gethd() const; size_t getsz() const;
};
#endif
