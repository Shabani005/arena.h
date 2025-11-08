#define AR_IMPLEMENTATION
#include "../arena.h"

int main(void){
  Arena *ar = ar_init(1024);
  
  int *x = ar_alloc(ar, sizeof(int));
  printf("allocated pointer: %p\n", x);

  *x = 5;
  printf("heap allocated value: %d\n", *x);
  return 0;
}
