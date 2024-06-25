#include "options.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void options(struct optionsObject* obj, int argc, char **argv){
  char *input = NULL;
  char *out = NULL;
  int c;
  while ((c = getopt (argc, argv, "i:o:")) != -1) {
    switch (c)
      {
      case 'i':
        input = optarg;
        break;
      case 'o':
        out = optarg;
        break;
      default:
        break;
      }
  }

  int index;
  int nbytes = 0;
  for (index = optind; index < argc; index++) {
    nbytes = atoll(argv[index]);
  }
  obj->input = input;
  obj->out = out;
  obj->nbytes = nbytes;
}