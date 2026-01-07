#include "allocator.h"
#include <cstddef>

using namespace std;

class worst_fit_allocator : public allocatorr 
{
public:
    memoryBlock* allocate(memoryBlock* head, size_t size) override 
    {
        memoryBlock* curr = head;
        memoryBlock* worst_block = nullptr;

        while (curr != nullptr) {
            if (curr->free && curr->sz >= size) {
                if (worst_block == nullptr || curr->sz > worst_block->sz) worst_block = curr;
            }
            curr = curr->next;
        }
        if (worst_block == nullptr) {
            return nullptr; 
        }
        if (worst_block->sz > size) {
            memoryBlock* new_block = new memoryBlock(worst_block->start + size, worst_block->sz - size);
            new_block->next = worst_block->next;
            new_block->prev = worst_block;
            if (worst_block->next != nullptr) worst_block->next->prev = new_block;
            worst_block->next = new_block;
            worst_block->sz = size;
        }

        worst_block->free = 0;
        worst_block->block_id = generate_block_id();
        return worst_block;
    }

    void deallocate(memoryBlock* block) override 
    {
        if (block == nullptr) return;
        block->free = true;
        block->block_id = -1;
        if (block->next != nullptr && block->next->free) {
            memoryBlock* next_block = block->next;
            block->sz += next_block->sz;
            block->next = next_block->next;
            if (next_block->next != nullptr) next_block->next->prev = block;
            delete next_block;
        }
        if (block->prev != nullptr && block->prev->free) {
            memoryBlock* prev_block = block->prev;
            prev_block->sz += block->sz;
            prev_block->next = block->next;
            if (block->next != nullptr) block->next->prev = prev_block;
            delete block;
        }
    }
    private:
    int generate_block_id() {
        static int nxt_id = 1;
        return nxt_id++;
    }
};
