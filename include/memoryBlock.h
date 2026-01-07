#ifndef memoryBlock_h
#define memoryBlock_h
#include <cstddef>
struct memoryBlock 
{
  int free;              
  int block_id;           
  size_t start;
  size_t sz;       
  memoryBlock* prev;    
  memoryBlock* next;    
  memoryBlock(size_t start_addr, size_t block_sz): free(1), block_id(-1), start(start_addr), sz(block_sz), prev(nullptr), next(nullptr) {}
};
#endif
