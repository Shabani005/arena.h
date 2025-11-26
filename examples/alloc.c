#include <stddef.h>
#define AR_IMPLEMENTATION
#include "../arena.h"

#undef AR_SIZE
#define AR_SIZE 10242239238238328

#define VEC_CAP 1000

int main(void){
    
  int *x = ar_alloc(sizeof(int) * VEC_CAP);
  printf("allocated pointer: %p\n", x);

  for (size_t i=0; i<1000; ++i){
    x[i] = i+1;
  }

  for (size_t i=0; i<1000; ++i){
    printf("heap allocated value: %d\n", x[i]);
  }

  while (1){
    
  }

  
  return 0;
}
