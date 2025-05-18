#include <sys/mman.h>
#include <unistd.h>

#include "heap.h"
#include "linkedList.c"

//Block *memory_remember = NULL;
Block *free_list = NULL;

#define MAX_SIZE (1024 * 128) // 128 KB

void* heap_alloc(size_t size)
{
    if (size == 0) return NULL;
    printf("size: %d\n", size);
    if (size <= MAX_SIZE && free_list != NULL) {
        Block *temp = free_list;
        while (temp != NULL) {
            if (temp->size >= size) { // first-fit
                Block* saved = temp;
                delete_node(&free_list, temp);
                printf("Memory was succesfully allocated from free list");
                return (void*)saved + 1;
            }
            temp = temp->next;
        }
    }

    Block *chunk;

    if (size >= MAX_SIZE) {
        chunk = (Block*)mmap(NULL, size + sizeof(Block),
                                                PROT_READ | PROT_WRITE,
                                                MAP_PRIVATE | MAP_ANONYMOUS,
                                                -1, 0);
        if (chunk == MAP_FAILED) return NULL;
        printf("Memory was succesfully allocated using mmap\n");
    } else {
        chunk = (Block*)sbrk(size + sizeof(Block));
        if (chunk == (void*)-1) {
            return NULL;
        }

        //append(&memory_remember, size);
    }

    chunk->size = size;
    chunk->next = NULL;
    
    printf("Chunk has been created succesfully:\n");
    //print_node(memory_remember);

    return (void*)(chunk + 1); // returning pointer on memory chunk (sbrk and mmap return it)
}

void heap_free(void* ptr)
{
    if (!ptr) {
        printf("Error occured!");
        return;
    }

    Block *chunk = (Block*)ptr - 1;
    printf("Chunk (free):\n");
    print_node(chunk);

    if (chunk->size >= MAX_SIZE) {
        if (munmap(chunk, chunk->size + sizeof(struct Block)) == 1) {
            printf(("munmap failed"));
        } else {
            printf("Memory deallocated using munmap, chunk size: %zu bytes\n", chunk->size);
        }
    } else {
        append(&free_list, chunk->size); // appending new el to free list
    }
}