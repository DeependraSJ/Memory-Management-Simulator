#ifndef cache_line_h
#define cache_line_h
#include <cstddef>
using namespace std;
struct cache_line 
{
    size_t tag;
    size_t inserted_at;
    bool valid;
    cache_line(): valid(false), tag(0), inserted_at(0) {}
};
#endif
