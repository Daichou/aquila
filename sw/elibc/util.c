// See LICENSE for license details.

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include "util.h"


extern volatile uint64_t tohost;
extern volatile uint64_t fromhost;


#define NUM_COUNTERS 2
static uintptr_t counters[NUM_COUNTERS];
static char* counter_names[NUM_COUNTERS];

void setStats(int enable)
{
  int i = 0;
#define READ_CTR(name) do { \
    while (i >= NUM_COUNTERS) ; \
    uintptr_t csr = read_csr(name); \
    if (!enable) { csr -= counters[i]; counter_names[i] = #name; } \
    counters[i++] = csr; \
  } while (0)

  READ_CTR(mcycle);
  READ_CTR(minstret);

#undef READ_CTR
}

void disStats()
{
    char buf[NUM_COUNTERS * 32] __attribute__((aligned(64)));
    char* pbuf = buf;
    for (int i = 0; i < NUM_COUNTERS; i++)
        if (counters[i])
            printf( "%s = %d\n", counter_names[i], counters[i]);
}
