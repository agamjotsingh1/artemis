#include <stdlib.h>
#include <byte.h>
#include <regfile.h>
#include <logger.h>

static byte regfile[REGFILE_LEN];

void write_reg(reg_t reg, byte val){
    if(reg >= 0 && reg <= REGFILE_LEN) {
        regfile[reg] = val;
    }
    else {
        ERROR("Invalid register (%d) requested...", reg);
    }
}

byte fetch_reg(reg_t reg){
    if(reg >= 0 && reg <= REGFILE_LEN) {
        return regfile[reg];
    }
    else {
        ERROR("Invalid register (%d) requested...", reg);
    }
}

dblbyte fetch_unif_reg(reg_unif_t reg){
    return ((fetch_reg(reg >> 4) & 0xFFFF) << 8)
            | (fetch_reg(reg & 0x0F) & 0xFFFF);
}

bool is_active_flag(flag_t flag){
    return ((fetch_reg(F) & flag) != 0x00);
}