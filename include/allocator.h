#ifndef allocator_h
#define allocator_h

#include <cstddef>
#include "memoryBlock.h"


class allocatorr
{
    public:
        virtual ~allocatorr() = default;
        virtual void deallocate(memoryBlock* block) = 0;
        virtual memoryBlock* allocate(memoryBlock* head, size_t sz) = 0;
};

#endif
