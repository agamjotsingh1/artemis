#include <stdlib.h>
#include <byte.h>
#include <regfile.h>
#include <logger.h>

regfile_t *init_regfile(){
    regfile_t *regfile = (regfile_t *) malloc(sizeof(regfile_t));

    if(regfile == NULL) {
        ERROR("Error generating RegFile, insufficient memory...");
    }

    for(int i = 0; i < REGFILE_LEN; i++) {
        regfile->regs[i] = 0x00;
    }

    return regfile;
}

void update_reg(regfile_t *regfile, reg_t reg, byte val){
    if(reg >= 0 && reg <= REGFILE_LEN) {
        regfile->regs[reg] = val;
    }
    else {
        ERROR("Invalid register (%d) requested...", reg);
    }
}

byte fetch_reg(regfile_t *regfile, reg_t reg){
    if(reg >= 0 && reg <= REGFILE_LEN) {
        return regfile->regs[reg];
    }
    else {
        ERROR("Invalid register (%d) requested...", reg);
    }
}

dblbyte fetch_unif_reg(regfile_t *regfile, reg_unif_t reg){
    return ((fetch_reg(regfile, reg >> 4) & 0xFFFF) << 8)
            | (fetch_reg(regfile, reg & 0x0F) & 0xFFFF);
}

bool is_active_flag(regfile_t *regfile, flag_t flag){
    return ((fetch_reg(regfile, F) & flag) != 0x00);
}