#include <unistd.h>

#include "heap.h"

void* heap_alloc(size_t size)
{
    if (size == 0) return NULL;

    void* takedMemory = (void*)sbrk(size);
    if (takedMemory == (void*)-1) {
        printf("Error occured!");
        return NULL;
    }

    struct Block *Chunk = sbrk(sizeof(size_t) + sizeof(struct Block*)); // creating struct 'Block' to save size of memory chunk (we need that for heap_free() func)
    Chunk->size = size;
    printf("Chunk has been created succesfully!\n");

    return takedMemory; // returning pointer on memory chunk (sbrk returns it)
}

void heap_free(void* ptr)
{
    if (!ptr) {
        printf("Error occured!");
        return;
    }


}