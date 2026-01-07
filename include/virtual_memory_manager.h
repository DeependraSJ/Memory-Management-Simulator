#ifndef virtual_memory_manager_h
#define virtual_memory_manager_h
using namespace std;
#include <cstddef>
#include <string>
#include "page_table.h"
#include "cachelevel.h"
class virtual_memory_manager 
{
private:
    size_t pgsz;
    size_t num_frames;
    page_table table;
    size_t time_counter;
    size_t next_free_frame;
    size_t pghits;
    size_t pgfaults;
    cache_level* L1;
    cache_level* L2;
    size_t choose_victim_page();
public:
    virtual_memory_manager(size_t virtual_mem_sz, size_t physical_mem_sz, size_t page_sz);
    void attach_caches(cache_level* L1_cache, cache_level* L2_cache);
    void access(size_t virtual_address);
    void print_stats() const;
};

#endif
