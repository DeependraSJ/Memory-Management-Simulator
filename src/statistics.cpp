#include "statistics.h"
#include <algorithm>
using namespace std;

statistics compute_statistics(memoryBlock* head, size_t total_memory, int allocation_success, int allocation_failure)
{
    statistics stats{};
    stats.free_memory = 0;
    stats.used_memory = 0;
    stats.total_memory = total_memory;
    stats.allocation_failure = allocation_failure;
    stats.allocation_success = allocation_success;
    size_t largest_free_block = 0;
    memoryBlock* current = head;
    while (current != nullptr) {
        if (current->free) {
            stats.free_memory += current->sz;
            largest_free_block = max(largest_free_block, current->sz);
        } 
        else {
            stats.used_memory += current->sz;
        }
        current = current->next;
    }
    if (stats.free_memory > 0) stats.external_fragmentation = 1.0 - (double)largest_free_block / stats.free_memory;
    else stats.external_fragmentation = 0.0;

    if (total_memory > 0) stats.memory_utilization = (double)stats.used_memory / total_memory; 
    else stats.memory_utilization = 0.0;
    return stats;
}
