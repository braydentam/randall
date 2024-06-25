#ifndef RAND64_SW_H
#define RAND64_SW_H

/* Initialize the software rand64 implementation.  */
void software_rand64_init (char* directory);

void software_lrand48_init (void);

/* Return a random value, using software operations.  */
unsigned long long software_rand64 (void);

unsigned long long software_lrand48(void);

/* Finalize the software rand64 implementation.  */
void software_rand64_fini (void);

#endif /* RAND64_SW_H */