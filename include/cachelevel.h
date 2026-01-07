#ifndef cache_level_h
#define cache_level_h
#include <vector>
#include <cstddef>
#include <string>
#include "cacheset.h"
using namespace std;
class cache_level 
{
private:
    string name;
    size_t cache_size;
    size_t block_size;
    size_t associativity;
    size_t num_sets;
    size_t time_counter;
    size_t hits;
    size_t misses;
    size_t get_set_index(size_t address) const;
    size_t get_tag(size_t address) const;
    vector<cache_set> sets;
    int choose_victim(cache_set& set);   
public:
    cache_level(string level_name, size_t cache_size, size_t block_size, size_t associativity);
    bool access(size_t address);
    void print_stats() const;
};
#endif
