
#ifndef __HEAP_SRCREIGH__
#define __HEAP_SRCREIGH__

#include <stdint.h>
#include <stdbool.h>

typedef struct Node {
   uint32_t priority;
   uint32_t value;
} Node;

typedef struct Heap {
   // the items in the heap
   Node *elements;
   // holds the size of the internal array
   uint32_t size;
   // holds the number of elements in the heap
   uint32_t numElements;
} Heap;

const uint32_t MIN_HEAP_SIZE;

/**
 * Returns true if the given heap is nil or empty.
 */
bool heap_empty(Heap *heap);

/**
 * Inititializes a heap and returns a pointer to the new heap.
 */
Heap *heap_init();

/**
 * Inserts, with given priority, a given element into the heap.
 */
void heap_insert(Heap *heap, uint32_t value, uint32_t priority);

/**
 * Deletes the maximum element from the heap, and returns the value of that
 * element.
 */
uint32_t heap_deleteMax(Heap *heap);

/**
 * Deletes the maximum element from the heap, and returns the value of that
 * element. Also takes a pointer that will be filled with the priority of the
 * deleted element.
 */
uint32_t heap_deleteMaxWithPriority(Heap *heap, uint32_t *priority);

/**
 * Cleans up a heap after allocation.
 */
void heap_free(Heap *heap);

#endif

