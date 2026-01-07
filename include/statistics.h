#ifndef statistics_h
#define statistics_h
#include <cstddef>
#include "memoryBlock.h"
using namespace std;
struct statistics {
    double external_fragmentation;
    double memory_utilization;
    size_t total_memory;
    size_t used_memory;
    size_t free_memory;
    int allocation_failure;
    int allocation_success;
};
statistics compute_statistics(memoryBlock* head, size_t total_memory, int allocation_success, int allocation_failure);
#endif
