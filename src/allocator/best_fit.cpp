#include "allocator.h"
#include <cstddef>
using namespace std;

class best_fit_allocator : 
public allocatorr 
{
public:
    memoryBlock* allocate(memoryBlock* head, size_t size) override 
    {
        memoryBlock* curr = head;
        memoryBlock* best_block = nullptr;
        while (curr != nullptr) {
            if (curr->free && curr->sz >= size) {
                if (best_block == nullptr || curr->sz < best_block->sz) {
                    best_block = curr;
                }
            }
            curr = curr->next;
        }
        if (best_block == nullptr) return nullptr;
        if (best_block->sz > size) 
        {
            memoryBlock* new_block = new memoryBlock(best_block->start + size, best_block->sz - size);
            new_block->next = best_block->next;
            new_block->prev = best_block;
            if (best_block->next != nullptr) best_block->next->prev = new_block;
            best_block->next = new_block;
            best_block->sz = size;
        }
        best_block->free = false;
        best_block->block_id = generate_block_id();
        return best_block;
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
        static int nxtid = 1;
        return nxtid++;
    }
};
