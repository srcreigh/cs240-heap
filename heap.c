
#include "heap.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define DEBUG 0
#if DEBUG
   #include <stdio.h>
#endif

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

const uint32_t MIN_HEAP_SIZE = 8;

static void bubbleUp(Heap*, uint32_t);
static void bubbleDown(Heap*, uint32_t);

Heap *heap_init() {
   Heap *heap = (Heap *)malloc(sizeof(Heap));

   heap->numElements = 0;
   heap->size = MIN_HEAP_SIZE;
   heap->elements = (Node *)malloc(heap->size * sizeof(Node));

   return heap;
}

bool heap_isEmpty(Heap* heap) {
   return heap == NULL || heap->elements == 0;
}

void heap_insert(Heap *heap, uint32_t value, uint32_t priority) {
   // The heap will always have at least 1 extra space for an element at
   // the end when this function ends.
   
   // Create the new node and add it to the available spot in the heap.
   Node node;
   node.priority = priority;
   node.value = value;

   uint32_t pos = heap->numElements;
   heap->elements[pos] = node;
   heap->numElements++;

   // "Bubble up" the new element
   bubbleUp(heap, pos);

   // Reallocate the elements array to twice the numElements if we're full
   if (heap->numElements == heap->size) {
      heap->size *= 2;
#if DEBUG
      printf("\nincreasing heap size to %u...\n\n", heap->size);
#endif
      heap->elements = realloc(heap->elements, heap->size * sizeof(Node));
   }
}

uint32_t heap_deleteMax(Heap *heap) {
   return heap_deleteMaxWithPriority(heap, NULL);
}

uint32_t heap_deleteMaxWithPriority(Heap *heap, uint32_t *priority) {
   Node max = heap->elements[0];
   if (priority) {
      *priority = max.priority;
   }

   // Put the last element at the top
   heap->elements[0] = heap->elements[heap->numElements - 1];
   heap->numElements--;

   // Bubble down
   bubbleDown(heap, 0);

   // Reallocate to a smaller array if necessary
   if (heap->numElements <= heap->size / 4) {

      int32_t newSize = MAX(MIN_HEAP_SIZE, heap->size / 2);
      heap->size = newSize;
#if DEBUG
      printf("\ndecreasing heap size to %u...\n\n", newSize);
#endif
      heap->elements = realloc(heap->elements, newSize * sizeof(Node));
   }

   return max.value;
}

void heap_free(Heap *heap) {
   free(heap->elements);
   free(heap);
}

static void bubbleUp(Heap *heap, uint32_t pos) {
   uint32_t parent = (pos - 1) / 2;

   // While it's not the root node, and is strictly greater priority than its 
   // parent...
   while (pos != 0 && 
          heap->elements[parent].priority < heap->elements[pos].priority) {

      // Swap with the parent
      Node swap = heap->elements[parent];
      heap->elements[parent] = heap->elements[pos];
      heap->elements[pos] = swap;

      // Calculate the new positions
      pos = parent;
      parent = (pos - 1) / 2;
   }
}

static void bubbleDown(Heap *heap, uint32_t pos) {
   while (true) {
      // Find the child with the greatest priority
      uint32_t left = 2 * pos + 1;
      uint32_t right = 2 * pos + 2;

      bool childrenExist = false;
      bool leftLargest = false;

      if (left < heap->numElements && right < heap->numElements) {
         childrenExist = true;
         if (heap->elements[left].priority > heap->elements[right].priority) {
            leftLargest = true;
         } else {
            leftLargest = false;
         }
      } else if (left < heap->numElements) {
         childrenExist = true;
         leftLargest = true;
      } else {
         childrenExist = false;
      }

      if (childrenExist) {
         // Check if the largest child's priority is larger than the current
         // node's priority

         uint32_t largestPos = leftLargest ? left : right;
         uint32_t priority = heap->elements[largestPos].priority;

         if (priority > heap->elements[pos].priority) {
            // Swap the elements
            Node swap = heap->elements[pos];
            heap->elements[pos] = heap->elements[largestPos];
            heap->elements[largestPos] = swap;

            // Replace the position for more bubbling down
            pos = largestPos;
         } else {
            break;
         }
      } else {
         break;
      }
   }
}
