#ifndef page_table_entry_h
#define page_table_entry_h
#include <cstddef>
using namespace std;

struct page_table_entry {
    bool valid;
    size_t frame;
    size_t loaded_at;   
    page_table_entry(): valid(false), frame(0), loaded_at(0) {}
};

#endif
