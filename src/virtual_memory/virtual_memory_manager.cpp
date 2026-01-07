#include "virtual_memory_manager.h"
#include <iostream>
#include <limits>
using namespace std;

virtual_memory_manager::virtual_memory_manager(size_t vm_sz, size_t pm_sz, size_t psize): pgsz(psize),
    num_frames(pm_sz / psize),
    table(vm_sz / psize),
    time_counter(0),
    next_free_frame(0),
    pghits(0),
    pgfaults(0),
    L1(nullptr),
    L2(nullptr)
{}

void virtual_memory_manager::attach_caches(cache_level* L1_cache, cache_level* L2_cache)
{
    L1 = L1_cache;
    L2 = L2_cache;
}
size_t virtual_memory_manager::choose_victim_page()
{
    size_t victim = 0;
    size_t oldest = numeric_limits<size_t>::max();
        for (size_t i = 0; i < table.entries.size(); i++) {
            if (table.entries[i].valid &&
                table.entries[i].loaded_at < oldest) {
                oldest = table.entries[i].loaded_at;
                victim = i;
            }
        }
    return victim;
}

void virtual_memory_manager::access(size_t virtual_address)
{
    time_counter++;
    size_t page = virtual_address / pgsz;
    size_t offset = virtual_address % pgsz;
    page_table_entry& entry = table.entries[page];
    if (entry.valid) {
        pghits++;
    } 
    else {
        pgfaults++;
        if (next_free_frame < num_frames) {
            entry.frame = next_free_frame++;
        } 
        else {
            size_t victim_page = choose_victim_page();
            entry.frame = table.entries[victim_page].frame;
            table.entries[victim_page].valid = false;
        }
        entry.valid = true;
        entry.loaded_at = time_counter;
    }
    size_t physical_address = entry.frame * pgsz + offset;
    if (L1 && !L1 -> access(physical_address)) {
        if (L2) L2->access(physical_address);
    }
}

void virtual_memory_manager::print_stats() const
{
    cout << "page hits: " << pghits << "\n";
    cout << "page faults: " << pgfaults << "\n";
}
