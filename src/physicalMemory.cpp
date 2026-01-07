#include "physicalMemory.h"
using namespace std;

physicalMemory::physicalMemory(size_t size): ttlsz(size), memory(size, 0),head(nullptr)
{
    head = new memoryBlock(0, ttlsz);
}
physicalMemory::~physicalMemory()
{
    memoryBlock* curr = head;
    while (curr != nullptr) {
        memoryBlock* nex_block = curr->next;
        delete curr;
        curr = nex_block;
    }
}
memoryBlock* physicalMemory::gethd() const
{
    return head;
}
size_t physicalMemory::getsz() const
{
    return ttlsz;
}
