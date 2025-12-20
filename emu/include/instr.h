#ifndef INSTR_DEF
#define INSTR_DEF

#include <byte.h>

typedef enum {
    IN_NONE, // For invalid or prefix opcodes
    IN_NOP,
    IN_LD,
    IN_LDH, 
    IN_PUSH,
    IN_POP,
    IN_ADD,
    IN_ADC,
    IN_SUB,
    IN_SBC,
    IN_AND,
    IN_OR,
    IN_XOR,
    IN_CP,
    IN_INC,
    IN_DEC,
    IN_DAA,
    IN_CPL,
    IN_RLCA,
    IN_RRCA,
    IN_RLA,
    IN_RRA,
    IN_RLC,
    IN_RRC,
    IN_RL,
    IN_RR,
    IN_SLA,
    IN_SRA,
    IN_SWAP,
    IN_SRL,
    IN_BIT,
    IN_SET,
    IN_RES,
    IN_JP,
    IN_JR,
    IN_CALL,
    IN_RET,
    IN_RETI,
    IN_RST,
    IN_DI,
    IN_EI,
    IN_HALT,
    IN_STOP,
    IN_SCF,
    IN_CCF
} instr_class_t;

typedef enum {
    AM_NONE,      // No operands (1-byte instruction)
    AM_R8,        // 8-bit register (e.g., B, C, D)
    AM_R16,       // 16-bit register pair (e.g., BC, HL)
    AM_IMM8,      // 8-bit immediate value (n8)
    AM_IMM16,     // 16-bit immediate value (n16)
    AM_S8,        // 8-bit signed offset (e8 for JR)
    AM_HL_INDIR,  // Memory at [HL]
    AM_HRAM       // High RAM / IO ($FF00 + n8)
} addr_mode_t;

typedef struct {
    byte cycles;
    len_t len;

    addr_mode_t addr_mode;
    instr_class_t instr_class;
} instr_t;

instr_t parse_instr(byte opcode);

#endif