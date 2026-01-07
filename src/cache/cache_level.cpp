#include "cachelevel.h"
#include <iostream>
#include <limits>
using namespace std;

cache_level::cache_level(string level_name, size_t csize, size_t bsize, size_t assoc):
    name(level_name),
    block_size(bsize),
    cache_size(csize),
    associativity(assoc),
    time_counter(0),
    hits(0),
    misses(0)
{
    num_sets = cache_size / (block_size * associativity);
    for (size_t i = 0; i < num_sets; i++) {
        sets.emplace_back(associativity);
    }
}
size_t cache_level::get_set_index(size_t address) const{
    return (address / block_size) % num_sets;
}
size_t cache_level::get_tag(size_t address) const{
    return address / (block_size * num_sets);
}

int cache_level::choose_victim(cache_set& set)
{
    int victim = 0;
    size_t oldest = numeric_limits<size_t>::max();
    for (size_t i = 0; i < set.lines.size(); i++) {
        if (!set.lines[i].valid) return i;
        if (set.lines[i].inserted_at < oldest) {
            oldest = set.lines[i].inserted_at;
            victim = i;
        }
    }
    return victim;
}
bool cache_level::access(size_t address)
{
    time_counter++;
    size_t set_index = get_set_index(address);
    size_t tag = get_tag(address);
    cache_set& set = sets[set_index];
    for (auto& line : set.lines) {
        if (line.valid && line.tag == tag) {
            hits++;
            return true;
        }
    }

    misses++;

    int victim = choose_victim(set);
    cache_line& line = set.lines[victim];
    line.valid = true;
    line.tag = tag;
    line.inserted_at = time_counter;

    return false;
}

void cache_level::print_stats() const
{
    cout << name << " hits: " << hits << "\n";
    cout << name << " misses: " << misses << "\n";
    double ratio = ((hits + misses) == 0 ? 0.0 : (double)hits / (hits + misses));
    cout << name << " hit ratio: " << ratio * 100 << "%\n";
}
