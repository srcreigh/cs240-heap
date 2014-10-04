
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main(int argc, const char *argv[]) {

   int seed = time(NULL);
   printf("seed: %d\n", seed);
   srand(seed);

   Heap *heap = heap_init();
   for (int i = 0; i < 10000; i++) {
      int r = rand() % 3;

      if (r != 0 || heap->numElements == 0) {
         uint32_t value = rand();
         uint32_t priority = rand();
         printf("inserting %u \twith priority %u\n", value, priority);
         heap_insert(heap, value, priority);

      } else {
         printf("deleteMax: %u\n", heap_deleteMax(heap));
      }
   }

   for (int i = 0; i < heap->numElements; i++) {
      uint32_t priority;
      uint32_t value = heap_deleteMaxWithPriority(heap, &priority);
      printf("deleteMax: %u \twith priority %u\n", value, priority);
   }
   heap_free(heap);

   return 0;
}
