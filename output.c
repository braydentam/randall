#include "output.h" 
#include "rand64-hw.h"
#include "rand64-sw.h"
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

_Bool writebytes (unsigned long long x, int nbytes)
{
  do
    {
      if (putchar (x) < 0)
	return false;
      x >>= CHAR_BIT;
      nbytes--;
    }
  while (0 < nbytes);

  return true;
}

void doNothing(void){}

int handle_output(char *input, char *output, int nbytes) {
   // Error handling for missing input or output
  if(input == NULL) input = "rdrand";
  if(output == NULL) output = "stdio";
  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);
  // Handle input options
  if (strcmp(input, "rdrand") == 0) {
    // Handles hardware case
    if (rdrand_supported ())
    {
        initialize = hardware_rand64_init;
        rand64 = hardware_rand64;
        finalize = hardware_rand64_fini;
        initialize ();
    }
    else{
      perror ("ERROR");
      return -1;
    }
  }
  else if (strcmp(input, "lrand48_r") == 0) {
      rand64 = software_lrand48;
      finalize = doNothing;
      software_lrand48_init();
  } 
  else {
      software_rand64_init(input);
      rand64 = software_rand64;
      finalize = software_rand64_fini;
  }
    // Initialize random function
  
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  if (strcmp(output, "stdio") == 0) {
  do
    {
        unsigned long long x = rand64 ();
        int outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (!writebytes (x, outbytes))
    {
        output_errno = errno;
        break;
    }
        nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
  output_errno = errno;

  if (output_errno)
    {
        errno = output_errno;
        perror ("output");
    }
  }  
  else {
      // Handle -o N option
      int n = atoi(output);
      char* buffer = malloc(n * 99999);
      int iter = 0;
      unsigned long long x;
      int outbytes;
      do{
        outbytes = nbytes < n ? nbytes : n;
        for(int j = 0;j < outbytes;j++){
          x = rand64();
          buffer[(iter * sizeof(char)) + j] = x;
        }
        write(1, buffer, outbytes);
        nbytes -= n;
        iter++;
      }
      while(nbytes > 0);
      free(buffer);
  }

  finalize();
  return !!output_errno;
}
