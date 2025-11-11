#include <stdint.h>
#include <sys/mman.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


#define AR_SIZE 1024*1024

typedef struct {
  uint8_t *base;
  size_t size;
  size_t capacity;
} Arena;

Arena *ar_init(size_t cap);
void * ar_alloc(Arena *a, size_t size);
void ar_free(Arena *a);
void arena_reset(Arena *a);

#ifdef AR_IMPLEMENTATION
// TODO: default static ARENA with AR_SIZE 
Arena *ar_init(size_t cap){
  Arena *a = malloc(sizeof(Arena));
  void *arena = mmap(NULL, cap, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  a->capacity = cap;
  a->size = 0;
  a->base = arena;

  return a;
}

void *ar_alloc(Arena *a, size_t size){
  void* ptr = a->base + a->size;
  a->size += size;
  return ptr;
}

void arena_reset(Arena *a){
  a->size = 0; // We just overwrite old data
}

void ar_free(Arena *a){
  if (a->base){
    munmap(a->base, a->capacity);
    free(a);
  }
}
#endif // AR_IMPLEMENTATION
