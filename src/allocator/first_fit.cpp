#include "allocator.h"
#include <cstddef>

using namespace std;

class first_fit_allocator : public allocatorr 
{
    public:
    memoryBlock* allocate (memoryBlock* head, size_t size) override 
    {
        memoryBlock* curr = head;
        while(curr != nullptr) {
            if(curr->free && curr->sz >= size) {
                if(curr->sz > size) {
                    memoryBlock* new_block = new memoryBlock(curr->start + size, curr->sz - size);
                    new_block->next = curr->next;
                    new_block->prev = curr;
                    if(curr->next != nullptr) curr->next->prev = new_block;
                    curr->next = new_block;
                    curr->sz = size;
                }
                curr->free = 0;
                curr->block_id = generate_block_id();
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }
    void deallocate(memoryBlock* block) override 
    {
        if(block == nullptr) return;
        block->free =  1;
        block->block_id = -1;
        if(block->next != nullptr && block->next->free) {
            memoryBlock* next_block = block->next;
            block->sz += next_block->sz;
            block->next = next_block->next;
            if(next_block->next != nullptr) {
                next_block->next->prev = block;
            }
            delete next_block;
        }

        if(block->prev != nullptr && block->prev->free) {
            memoryBlock* prev_block = block->prev;
            prev_block->sz += block->sz;
            prev_block->next = block->next;
            if(block->next != nullptr) block->next->prev = prev_block;
            delete block;
        }
    }
    private:
        int generate_block_id() {
            static int nxtid = 1;
            return nxtid++;
        }
};