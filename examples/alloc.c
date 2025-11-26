#include <stddef.h>
#define AR_IMPLEMENTATION
#include "../arena.h"

#define VEC_CAP 10

int main(void){
    
  int *x = ar_alloc(sizeof(int) * VEC_CAP);
  printf("allocated pointer: %p\n", x);

  for (size_t i=0; i<10; ++i){
    x[i] = i+1;
  }

  for (size_t i=0; i<10; ++i){
    printf("heap allocated value: %d\n", x[i]);
  }
  
  return 0;
}
