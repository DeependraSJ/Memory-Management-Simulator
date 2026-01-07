#include "memoryManage.h"
#include "statistics.h"
#include <iostream>
using namespace std;

memoryManager::memoryManager(size_t memory_size): memory(memory_size), current_allocator(nullptr), allocation_success(0), allocation_failure(0) {}


void memoryManager::set_allocator(allocatorr* alloc){
    current_allocator = alloc;
}

int memoryManager::malloc_block(size_t size){
    if (current_allocator == nullptr) {
        cout << "allocator not set!\n";
        return -1;
    }
    memoryBlock* block = current_allocator->allocate(memory.gethd(), size);
    if (block == nullptr) {
        allocation_failure++;
        return -1;
    }
    allocation_success++;
    allocated_blocks[block->block_id] = block;
    return block->block_id;
}

void memoryManager::free_block(int block_id){
    auto it = allocated_blocks.find(block_id);
    if (it == allocated_blocks.end()) {
        cout << "Invalid block ID!\n";
        return;
    }
    memoryBlock* block = it->second;
    current_allocator->deallocate(block);
    allocated_blocks.erase(it);
}

memoryBlock* memoryManager::get_head() const{
    return memory.gethd();
}

size_t memoryManager::getnetsz() const{
    return memory.getsz();
}

void memoryManager::dump_memory() const{
memoryBlock* curr = memory.gethd();
    while (curr != nullptr) {
        size_t start = curr->start;
        size_t end = curr->start + curr->sz - 1;
        if (curr->free) {
            cout << "0x" << hex << start << " to 0x" << end << " free\n";
        } 
        else {
            cout << "0x" << hex << start << " to 0x" << end << " used (block_id=" << dec << curr->block_id << ")\n";
        }
        curr = curr->next;
    }
    cout << dec;

}

void memoryManager::print_stats() const
{
    statistics stats = compute_statistics(
        memory.gethd(),
        memory.getsz(),
        allocation_success,     
        allocation_failure
    );
    
    cout << "Used Memory:- " << stats.used_memory << " units\n";
    cout << "Free Memory:- " << stats.free_memory << " units\n";
    cout << "Total Memory:- " << stats.total_memory << " units\n";
    cout << "Memory Utilization:- " << stats.memory_utilization * 100 << "%\n";
    cout << "External Fragmentation:- " << stats.external_fragmentation * 100 << "%\n";
    cout << "Successful Allocation:- " << stats.allocation_success << "\n";
}