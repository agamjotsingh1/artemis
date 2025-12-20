#ifndef CPU_DEF
#define CPU_DEF

#include <byte.h>
#include <regfile.h>

#define ENTRY_PC 0x100

typedef struct {
    regfile_t *regfile;
    unsigned int pc;
} cpu_ctx_t;

#endif