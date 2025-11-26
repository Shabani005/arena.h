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
void * ar_alloc_generic(Arena *a, size_t size);
void ar_free_generic(Arena *a);
void ar_reset_generic(Arena *a);

static Arena *default_arena = NULL;

static void ensure_default_arena(void) {
  if (!default_arena) {
    default_arena = ar_init(AR_SIZE);
  }
}

#define ar_alloc(size)  ( ensure_default_arena(), ar_alloc_generic(default_arena, size) )
#define ar_free()       ( ensure_default_arena(), ar_free_generic(default_arena) )
#define ar_reset()      ( ensure_default_arena(), ar_reset_generic(default_arena) )

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

void *ar_alloc_generic(Arena *a, size_t size){
  if (a->size + size > a->capacity) { 
    fprintf(stderr, "Writing into out of bounds memory\n");
    abort();
  }
  void* ptr = a->base + a->size;
  a->size += size;
  return ptr;
}

void ar_reset_generic(Arena *a){
  a->size = 0; // We just overwrite old data
}

void ar_free_generic(Arena *a){
  if (a->base){
    munmap(a->base, a->capacity);
    free(a);
  }
}
#endif // AR_IMPLEMENTATION
