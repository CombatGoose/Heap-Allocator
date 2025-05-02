#include <sys/mman.h>
#include <unistd.h>

#include "heap.h"
#include "linkedList.c"

struct Block *memory_remember = NULL;
struct Block *free_list = NULL;

#define MAX_SIZE (1024 * 128) // 128 KB

void* heap_alloc(size_t size)
{
    if (size == 0) return NULL;
    printf("size: %d\n", size);
    if (size <= MAX_SIZE) {
        struct Block *temp = free_list;
        print_node(free_list);
        while (temp != NULL) {
            printf("first bober");
            if (temp->size >= size) { // first-fit
                struct Block* saved = temp;
                delete_node(&free_list, temp);
                printf("bober");
                print_node(free_list);

                return (void*)saved;
            }
            temp = temp->next;
        }
    }

    struct Block *chunk;

    if (size >= MAX_SIZE) {
        chunk = (struct Block*)mmap(NULL, size + sizeof(struct Block),
                                                PROT_READ | PROT_WRITE,
                                                MAP_PRIVATE | MAP_ANONYMOUS,
                                                -1, 0);
        if (chunk == MAP_FAILED) return NULL;
        printf("Memory was succesfully allocated using mmap\n");
    } else {
        chunk = (struct Block*)sbrk(size + sizeof(struct Block));
        if (chunk == (void*)-1) {
            return NULL;
        }

        append(&memory_remember, size);
    }
    
    printf("Chunk has been created succesfully:\n");
    print_node(memory_remember);

    return (void*)chunk; // returning pointer on memory chunk (sbrk and mmap return it)
}

void heap_free(void* ptr)
{
    if (!ptr) {
        printf("Error occured!");
        return;
    }

    struct Block *chunk = (struct Block*)((char*)ptr - sizeof(struct Block));

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