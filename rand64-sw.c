#include "rand64-sw.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // for time

/* Software implementation.  */

/* Input stream containing random bytes.  */
FILE *urandstream;

/* Initialize the software rand64 implementation.  */
void
software_rand64_init (char* directory)
{
  urandstream = fopen (directory, "r");
  if (!urandstream) {
    perror("no file found");
    abort();
  }
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

struct drand48_data state;

void
software_lrand48_init (void)
{
  srand48_r(time(NULL), &state);
}

unsigned long long 
software_lrand48(void){
  long int data, data_two;
  unsigned long long final;
  // Get random value
  mrand48_r(&state, &data);
  mrand48_r(&state, &data_two);

  final = (((unsigned long long) data << 32) | (unsigned long long) data_two);
  return final;
}
/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void)
{
  fclose (urandstream);
}