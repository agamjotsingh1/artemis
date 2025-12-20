#include <cpu.h>
#include <instr.h>

static cpu_ctx_t cpu_ctx;

void cpu_cold_start() {
    cpu_ctx.pc = ENTRY_PC;
    cpu_ctx.regfile = init_regfile();
}

byte gobble_byte(byte* cart_data){
    byte val = cart_data[cpu_ctx.pc];
    cpu_ctx.pc += 1;
    return val;
}

instr_t cpu_fetch_instr(byte* cart_data){
    byte opcode = gobble_byte(cart_data);
    return parse_instr(opcode);
}

void cpu_exec(byte* data){

}