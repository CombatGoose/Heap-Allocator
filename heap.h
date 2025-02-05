#ifndef HEAP
#define HEAP

#include <stdio.h>

typedef struct Block {
    size_t size;
    struct Block *next;
} Block;

void* heap_alloc(size_t size);
void heap_free(void* ptr);

#endif