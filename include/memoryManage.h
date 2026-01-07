#ifndef memoryManage_h
#define memoryManage_h
#include <cstddef>
#include <unordered_map>
#include "physicalMemory.h"
#include "allocator.h"
using namespace std;
class memoryManager {
private:
    physicalMemory memory;
    allocatorr* current_allocator;
    unordered_map<int, memoryBlock*> allocated_blocks;
    int allocation_success;
    int allocation_failure;
public:
    memoryManager(size_t mem_sz);
    void set_allocator(allocatorr* alloc);
    int malloc_block(size_t sz);
    void free_block(int block_id);
    memoryBlock* get_head() const;
    size_t getnetsz() const;
    void dump_memory() const;
    void print_stats() const;
};

#endif
