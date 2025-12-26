#ifndef INSTR_DEF
#define INSTR_DEF

#include <byte.h>
#include <regfile.h>

typedef enum {
    IN_NONE, IN_NOP, IN_LD, IN_LDH, IN_PUSH, IN_POP, IN_ADD, IN_ADC, IN_SUB, IN_SBC,
    IN_AND, IN_OR, IN_XOR, IN_CP, IN_INC, IN_DEC, IN_DAA, IN_CPL, IN_RLCA, IN_RRCA,
    IN_RLA, IN_RRA, IN_RLC, IN_RRC, IN_RL, IN_RR, IN_SLA, IN_SRA, IN_SWAP, IN_SRL,
    IN_BIT, IN_SET, IN_RES, IN_JP, IN_JR, IN_CALL, IN_RET, IN_RETI, IN_RST,
    IN_DI, IN_EI, IN_HALT, IN_STOP, IN_SCF, IN_CCF
} instr_class_t;

typedef enum {
    OT_NONE,
    OT_R8,         // Register 8-bit
    OT_R16,        // Register 16-bit
    OT_IMM8,       // Immediate 8-bit (n8)
    OT_IMM16,      // Immediate 16-bit (n16)
    OT_IMM8_SIGNED,// Signed 8-bit offset (e8)
    OT_MEM_R16,    // Memory at register [(BC), (DE), (HL)]
    OT_MEM_IMM16,  // Memory at immediate address [(a16)]
    OT_MEM_HL_INC, // Memory at HL, then increment HL [(HL+)]
    OT_MEM_HL_DEC, // Memory at HL, then decrement HL [(HL-)]
    OT_MEM_IO_IMM8,// IO port at $FF00 + n8
    OT_MEM_IO_C,   // IO port at $FF00 + C
    OT_SP_HL,      // Special case for LD SP, HL
    OT_SP_OFFSET   // SP + e8 (for LD HL, SP+e8)
} op_type_t;

typedef enum {
    CT_NONE, CT_NZ, CT_Z, CT_NC, CT_C
} cond_t;

typedef struct {
    op_type_t type;
    union {
        reg_t r8;
        reg_unif_t r16;
        byte imm; // For fixed immediates (RST vectors, Bit indices)
    } reg;
} op_t;

typedef struct {
    byte cycles;
    len_t len;
    
    instr_class_t instr_class;
    op_t op1; // Destination or first operand
    op_t op2; // Source or second operand
    cond_t cond; // Condition for jumps/calls/rets
} instr_t;

instr_t parse_instr(byte opcode);

#endif