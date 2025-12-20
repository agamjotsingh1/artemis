#ifndef MEM_DEF
#define MEM_DEF

#include <byte.h>

typedef dblbyte addr_t;

typedef struct {
    dblbyte size;
    byte* data;
} mem_t;

mem_t *init_mem(dblbyte size);
void update_mem(mem_t *mem, addr_t addr, byte val);
void fetch_mem(mem_t *mem, addr_t addr);

#endif