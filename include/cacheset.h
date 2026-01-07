#ifndef cache_set_h
#define cache_set_h
#include <vector>
#include "cacheline.h"
using namespace std;
struct cache_set 
{
    vector<cache_line> lines;
    cache_set(size_t associativity): lines(associativity) {}
};
#endif
