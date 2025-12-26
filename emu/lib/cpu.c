#include <cpu.h>
#include <logger.h>
#include <instr.h>
#include <mem.h>

static cpu_ctx_t cpu_ctx;

byte gobble_byte(){
    byte val = mem_fetch(cpu_ctx.pc);
    cpu_ctx.pc += 1;
    return val;
}

instr_t fetch_instr(){
    byte opcode = gobble_byte();
    return parse_instr(opcode);
}

void cpu_cold_start() {
    cpu_ctx.pc = ENTRY_PC;
}

void cpu_exec_once(){
    while(1) {
        instr_t instr = fetch_instr();

        switch(instr.instr_class) {
            case IN_NONE: {
                ERROR("Invalid instruction provided!");
                break;
            }

            case IN_NOP: {
                break;
            }

            case IN_LD: {
                switch(instr.addr_mode) {
                    case AM_NONE:
                        break;

                    case AM_R8:
                    
                    default:
                        break;
                }
                break;
            }
            
            default:
                break;
        }
    }
}