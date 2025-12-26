#ifndef BYTE_DEF
#define BYTE_DEF

#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t dblbyte;

typedef enum {
    NIBBLE,
    BYTE,
    DBLBYTE,
    TRIBYTE,
    QUADBYTE
} len_t;

#endif