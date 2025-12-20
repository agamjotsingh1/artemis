#include <mem.h>
#include <logger.h>
#include <byte.h>

mem_t *init_mem(dblbyte size) {
    mem_t *mem = (mem_t *) malloc(sizeof(mem_t));
    mem->size = size;
    mem->data = malloc(sizeof(byte) * size);
    return mem;
}

void update_mem(mem_t *mem, addr_t addr, byte val){
    if(addr >= mem->size) {
        ERROR("Memory out of range!");
    }

    (mem->data)[addr] = val;
}

void fetch_mem(mem_t *mem, addr_t addr){
    if(addr >= mem->size) {
        ERROR("Memory out of range!");
    }

    return (mem->data)[addr];
}