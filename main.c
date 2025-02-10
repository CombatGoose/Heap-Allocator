#include <stdio.h>

#include "heap.c"

#define SIZE (1024 * 1024 * 100)

int main(void)
{
    int* arr = (int*)heap_alloc(SIZE * sizeof(int));
    if (!arr) {
        printf("Segmentation fault!");
        return 1;
    }

    char c;
    scanf("%c", &c);

    int* second_arr = (int*)heap_alloc(5 * sizeof(int));

    /*for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    for (int i  = 0; i < SIZE; i++) {
        printf("%d\n", arr[i]);
    }*/
    
    return 0;
}