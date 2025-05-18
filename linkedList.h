#include "heap.h"

Block* init_node(int size);
void append(Block** head, int size);
void print_node(Block* head);
void delete_node(Block** head, Block* ptr);