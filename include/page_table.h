#ifndef page_table_h
#define page_table_h
using namespace std;
#include <vector>
#include "pagetableentry.h"

class page_table {
public:
    vector<page_table_entry> entries;
    page_table(size_t num_pages): entries(num_pages) {}
};

#endif
