#define NB_IMPLEMENTATION
#include "nb.h"

int main(int argc, char** argv){
  nb_rebuild(argc, argv);

  nb_arr cmd = {0};

  nb_append_da(&cmd, "cc");
  nb_append_da(&cmd, "-o", "alloc");
  nb_append_da(&cmd, "examples/alloc.c");
  nb_cmd(&cmd);

  nb_append(&cmd, "./alloc");
  nb_cmd(&cmd);

  return 0;
}
