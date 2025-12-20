#include <stdio.h>
#include <stdint.h>

#include <cart.h>
#include <regfile.h>
#include <logger.h>

int main(){
    // cart_load("roms/pokemon_red.gb");
    // cart_load("roms/dmg-acid2.gb");
    regfile_t* regfile = init_regfile();
    update_reg(regfile, B, 0xAE);
    update_reg(regfile, F, 0x80);
    // LOG("Register value at BC = 0x%X", fetch_unif_reg(regfile, BC));
    LOG("Is zero flag? %x", is_active_flag(regfile, h));
    return 0;
}
