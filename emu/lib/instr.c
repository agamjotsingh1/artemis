#include <instr.h>

static const instr_t INSTR_LOOKUP[256] = {
    // 0x0X
    [0x00] = { 4, 1, AM_NONE, IN_NOP }, [0x01] = { 12, 3, AM_IMM16, IN_LD },
    [0x02] = { 8, 1, AM_NONE, IN_LD }, [0x03] = { 8, 1, AM_R16, IN_INC },
    [0x04] = { 4, 1, AM_R8, IN_INC }, [0x05] = { 4, 1, AM_R8, IN_DEC },
    [0x06] = { 8, 2, AM_IMM8, IN_LD }, [0x07] = { 4, 1, AM_NONE, IN_RLCA },
    [0x08] = { 20, 3, AM_IMM16, IN_LD }, [0x09] = { 8, 1, AM_R16, IN_ADD },
    [0x0A] = { 8, 1, AM_NONE, IN_LD }, [0x0B] = { 8, 1, AM_R16, IN_DEC },
    [0x0C] = { 4, 1, AM_R8, IN_INC }, [0x0D] = { 4, 1, AM_R8, IN_DEC },
    [0x0E] = { 8, 2, AM_IMM8, IN_LD }, [0x0F] = { 4, 1, AM_NONE, IN_RRCA },

    // 0x1X
    [0x10] = { 4, 2, AM_NONE, IN_STOP }, [0x11] = { 12, 3, AM_IMM16, IN_LD },
    [0x12] = { 8, 1, AM_NONE, IN_LD }, [0x13] = { 8, 1, AM_R16, IN_INC },
    [0x14] = { 4, 1, AM_R8, IN_INC }, [0x15] = { 4, 1, AM_R8, IN_DEC },
    [0x16] = { 8, 2, AM_IMM8, IN_LD }, [0x17] = { 4, 1, AM_NONE, IN_RLA },
    [0x18] = { 12, 2, AM_S8, IN_JR }, [0x19] = { 8, 1, AM_R16, IN_ADD },
    [0x1A] = { 8, 1, AM_NONE, IN_LD }, [0x1B] = { 8, 1, AM_R16, IN_DEC },
    [0x1C] = { 4, 1, AM_R8, IN_INC }, [0x1D] = { 4, 1, AM_R8, IN_DEC },
    [0x1E] = { 8, 2, AM_IMM8, IN_LD }, [0x1F] = { 4, 1, AM_NONE, IN_RRA },

    // 0x2X
    [0x20] = { 8, 2, AM_S8, IN_JR }, [0x21] = { 12, 3, AM_IMM16, IN_LD },
    [0x22] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x23] = { 8, 1, AM_R16, IN_INC },
    [0x24] = { 4, 1, AM_R8, IN_INC }, [0x25] = { 4, 1, AM_R8, IN_DEC },
    [0x26] = { 8, 2, AM_IMM8, IN_LD }, [0x27] = { 4, 1, AM_NONE, IN_DAA },
    [0x28] = { 8, 2, AM_S8, IN_JR }, [0x29] = { 8, 1, AM_R16, IN_ADD },
    [0x2A] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x2B] = { 8, 1, AM_R16, IN_DEC },
    [0x2C] = { 4, 1, AM_R8, IN_INC }, [0x2D] = { 4, 1, AM_R8, IN_DEC },
    [0x2E] = { 8, 2, AM_IMM8, IN_LD }, [0x2F] = { 4, 1, AM_NONE, IN_CPL },

    // 0x3X
    [0x30] = { 8, 2, AM_S8, IN_JR }, [0x31] = { 12, 3, AM_IMM16, IN_LD },
    [0x32] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x33] = { 8, 1, AM_R16, IN_INC },
    [0x34] = { 12, 1, AM_HL_INDIR, IN_INC }, [0x35] = { 12, 1, AM_HL_INDIR, IN_DEC },
    [0x36] = { 12, 2, AM_IMM8, IN_LD }, [0x37] = { 4, 1, AM_NONE, IN_SCF },
    [0x38] = { 8, 2, AM_S8, IN_JR }, [0x39] = { 8, 1, AM_R16, IN_ADD },
    [0x3A] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x3B] = { 8, 1, AM_R16, IN_DEC },
    [0x3C] = { 4, 1, AM_R8, IN_INC }, [0x3D] = { 4, 1, AM_R8, IN_DEC },
    [0x3E] = { 8, 2, AM_IMM8, IN_LD }, [0x3F] = { 4, 1, AM_NONE, IN_CCF },

    // 0x4X
    [0x40] = { 4, 1, AM_R8, IN_LD }, [0x41] = { 4, 1, AM_R8, IN_LD },
    [0x42] = { 4, 1, AM_R8, IN_LD }, [0x43] = { 4, 1, AM_R8, IN_LD },
    [0x44] = { 4, 1, AM_R8, IN_LD }, [0x45] = { 4, 1, AM_R8, IN_LD },
    [0x46] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x47] = { 4, 1, AM_R8, IN_LD },
    [0x48] = { 4, 1, AM_R8, IN_LD }, [0x49] = { 4, 1, AM_R8, IN_LD },
    [0x4A] = { 4, 1, AM_R8, IN_LD }, [0x4B] = { 4, 1, AM_R8, IN_LD },
    [0x4C] = { 4, 1, AM_R8, IN_LD }, [0x4D] = { 4, 1, AM_R8, IN_LD },
    [0x4E] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x4F] = { 4, 1, AM_R8, IN_LD },

    // 0x5X
    [0x50] = { 4, 1, AM_R8, IN_LD }, [0x51] = { 4, 1, AM_R8, IN_LD },
    [0x52] = { 4, 1, AM_R8, IN_LD }, [0x53] = { 4, 1, AM_R8, IN_LD },
    [0x54] = { 4, 1, AM_R8, IN_LD }, [0x55] = { 4, 1, AM_R8, IN_LD },
    [0x56] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x57] = { 4, 1, AM_R8, IN_LD },
    [0x58] = { 4, 1, AM_R8, IN_LD }, [0x59] = { 4, 1, AM_R8, IN_LD },
    [0x5A] = { 4, 1, AM_R8, IN_LD }, [0x5B] = { 4, 1, AM_R8, IN_LD },
    [0x5C] = { 4, 1, AM_R8, IN_LD }, [0x5D] = { 4, 1, AM_R8, IN_LD },
    [0x5E] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x5F] = { 4, 1, AM_R8, IN_LD },

    // 0x6X
    [0x60] = { 4, 1, AM_R8, IN_LD }, [0x61] = { 4, 1, AM_R8, IN_LD },
    [0x62] = { 4, 1, AM_R8, IN_LD }, [0x63] = { 4, 1, AM_R8, IN_LD },
    [0x64] = { 4, 1, AM_R8, IN_LD }, [0x65] = { 4, 1, AM_R8, IN_LD },
    [0x66] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x67] = { 4, 1, AM_R8, IN_LD },
    [0x68] = { 4, 1, AM_R8, IN_LD }, [0x69] = { 4, 1, AM_R8, IN_LD },
    [0x6A] = { 4, 1, AM_R8, IN_LD }, [0x6B] = { 4, 1, AM_R8, IN_LD },
    [0x6C] = { 4, 1, AM_R8, IN_LD }, [0x6D] = { 4, 1, AM_R8, IN_LD },
    [0x6E] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x6F] = { 4, 1, AM_R8, IN_LD },

    // 0x7X
    [0x70] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x71] = { 8, 1, AM_HL_INDIR, IN_LD },
    [0x72] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x73] = { 8, 1, AM_HL_INDIR, IN_LD },
    [0x74] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x75] = { 8, 1, AM_HL_INDIR, IN_LD },
    [0x76] = { 4, 1, AM_NONE, IN_HALT }, [0x77] = { 8, 1, AM_HL_INDIR, IN_LD },
    [0x78] = { 4, 1, AM_R8, IN_LD }, [0x79] = { 4, 1, AM_R8, IN_LD },
    [0x7A] = { 4, 1, AM_R8, IN_LD }, [0x7B] = { 4, 1, AM_R8, IN_LD },
    [0x7C] = { 4, 1, AM_R8, IN_LD }, [0x7D] = { 4, 1, AM_R8, IN_LD },
    [0x7E] = { 8, 1, AM_HL_INDIR, IN_LD }, [0x7F] = { 4, 1, AM_R8, IN_LD },

    // 0x8X
    [0x80] = { 4, 1, AM_R8, IN_ADD }, [0x81] = { 4, 1, AM_R8, IN_ADD },
    [0x82] = { 4, 1, AM_R8, IN_ADD }, [0x83] = { 4, 1, AM_R8, IN_ADD },
    [0x84] = { 4, 1, AM_R8, IN_ADD }, [0x85] = { 4, 1, AM_R8, IN_ADD },
    [0x86] = { 8, 1, AM_HL_INDIR, IN_ADD }, [0x87] = { 4, 1, AM_R8, IN_ADD },
    [0x88] = { 4, 1, AM_R8, IN_ADC }, [0x89] = { 4, 1, AM_R8, IN_ADC },
    [0x8A] = { 4, 1, AM_R8, IN_ADC }, [0x8B] = { 4, 1, AM_R8, IN_ADC },
    [0x8C] = { 4, 1, AM_R8, IN_ADC }, [0x8D] = { 4, 1, AM_R8, IN_ADC },
    [0x8E] = { 8, 1, AM_HL_INDIR, IN_ADC }, [0x8F] = { 4, 1, AM_R8, IN_ADC },

    // 0x9X
    [0x90] = { 4, 1, AM_R8, IN_SUB }, [0x91] = { 4, 1, AM_R8, IN_SUB },
    [0x92] = { 4, 1, AM_R8, IN_SUB }, [0x93] = { 4, 1, AM_R8, IN_SUB },
    [0x94] = { 4, 1, AM_R8, IN_SUB }, [0x95] = { 4, 1, AM_R8, IN_SUB },
    [0x96] = { 8, 1, AM_HL_INDIR, IN_SUB }, [0x97] = { 4, 1, AM_R8, IN_SUB },
    [0x98] = { 4, 1, AM_R8, IN_SBC }, [0x99] = { 4, 1, AM_R8, IN_SBC },
    [0x9A] = { 4, 1, AM_R8, IN_SBC }, [0x9B] = { 4, 1, AM_R8, IN_SBC },
    [0x9C] = { 4, 1, AM_R8, IN_SBC }, [0x9D] = { 4, 1, AM_R8, IN_SBC },
    [0x9E] = { 8, 1, AM_HL_INDIR, IN_SBC }, [0x9F] = { 4, 1, AM_R8, IN_SBC },

    // 0xAX
    [0xA0] = { 4, 1, AM_R8, IN_AND }, [0xA1] = { 4, 1, AM_R8, IN_AND },
    [0xA2] = { 4, 1, AM_R8, IN_AND }, [0xA3] = { 4, 1, AM_R8, IN_AND },
    [0xA4] = { 4, 1, AM_R8, IN_AND }, [0xA5] = { 4, 1, AM_R8, IN_AND },
    [0xA6] = { 8, 1, AM_HL_INDIR, IN_AND }, [0xA7] = { 4, 1, AM_R8, IN_AND },
    [0xA8] = { 4, 1, AM_R8, IN_XOR }, [0xA9] = { 4, 1, AM_R8, IN_XOR },
    [0xAA] = { 4, 1, AM_R8, IN_XOR }, [0xAB] = { 4, 1, AM_R8, IN_XOR },
    [0xAC] = { 4, 1, AM_R8, IN_XOR }, [0xAD] = { 4, 1, AM_R8, IN_XOR },
    [0xAE] = { 8, 1, AM_HL_INDIR, IN_XOR }, [0xAF] = { 4, 1, AM_R8, IN_XOR },

    // 0xBX
    [0xB0] = { 4, 1, AM_R8, IN_OR }, [0xB1] = { 4, 1, AM_R8, IN_OR },
    [0xB2] = { 4, 1, AM_R8, IN_OR }, [0xB3] = { 4, 1, AM_R8, IN_OR },
    [0xB4] = { 4, 1, AM_R8, IN_OR }, [0xB5] = { 4, 1, AM_R8, IN_OR },
    [0xB6] = { 8, 1, AM_HL_INDIR, IN_OR }, [0xB7] = { 4, 1, AM_R8, IN_OR },
    [0xB8] = { 4, 1, AM_R8, IN_CP }, [0xB9] = { 4, 1, AM_R8, IN_CP },
    [0xBA] = { 4, 1, AM_R8, IN_CP }, [0xBB] = { 4, 1, AM_R8, IN_CP },
    [0xBC] = { 4, 1, AM_R8, IN_CP }, [0xBD] = { 4, 1, AM_R8, IN_CP },
    [0xBE] = { 8, 1, AM_HL_INDIR, IN_CP }, [0xBF] = { 4, 1, AM_R8, IN_CP },

    // 0xCX
    [0xC0] = { 8, 1, AM_NONE, IN_RET }, [0xC1] = { 12, 1, AM_NONE, IN_POP },
    [0xC2] = { 12, 3, AM_IMM16, IN_JP }, [0xC3] = { 16, 3, AM_IMM16, IN_JP },
    [0xC4] = { 12, 3, AM_IMM16, IN_CALL }, [0xC5] = { 16, 1, AM_NONE, IN_PUSH },
    [0xC6] = { 8, 2, AM_IMM8, IN_ADD }, [0xC7] = { 16, 1, AM_NONE, IN_RST },
    [0xC8] = { 8, 1, AM_NONE, IN_RET }, [0xC9] = { 16, 1, AM_NONE, IN_RET },
    [0xCA] = { 12, 3, AM_IMM16, IN_JP }, [0xCB] = { 4, 1, AM_NONE, IN_NONE },
    [0xCC] = { 12, 3, AM_IMM16, IN_CALL }, [0xCD] = { 24, 3, AM_IMM16, IN_CALL },
    [0xCE] = { 8, 2, AM_IMM8, IN_ADC }, [0xCF] = { 16, 1, AM_NONE, IN_RST },

    // 0xDX
    [0xD0] = { 8, 1, AM_NONE, IN_RET }, [0xD1] = { 12, 1, AM_NONE, IN_POP },
    [0xD2] = { 12, 3, AM_IMM16, IN_JP }, [0xD3] = { 0, 0, AM_NONE, IN_NONE }, // Invalid
    [0xD4] = { 12, 3, AM_IMM16, IN_CALL }, [0xD5] = { 16, 1, AM_NONE, IN_PUSH },
    [0xD6] = { 8, 2, AM_IMM8, IN_SUB }, [0xD7] = { 16, 1, AM_NONE, IN_RST },
    [0xD8] = { 8, 1, AM_NONE, IN_RET }, [0xD9] = { 16, 1, AM_NONE, IN_RETI },
    [0xDA] = { 12, 3, AM_IMM16, IN_JP }, [0xDB] = { 0, 0, AM_NONE, IN_NONE }, // Invalid
    [0xDC] = { 12, 3, AM_IMM16, IN_CALL }, [0xDD] = { 0, 0, AM_NONE, IN_NONE }, // Invalid
    [0xDE] = { 8, 2, AM_IMM8, IN_SBC }, [0xDF] = { 16, 1, AM_NONE, IN_RST },

    // 0xEX
    [0xE0] = { 12, 2, AM_HRAM, IN_LDH }, [0xE1] = { 12, 1, AM_NONE, IN_POP },
    [0xE2] = { 8, 1, AM_NONE, IN_LDH }, [0xE3] = { 0, 0, AM_NONE, IN_NONE }, // Invalid
    [0xE4] = { 0, 0, AM_NONE, IN_NONE }, [0xE5] = { 16, 1, AM_NONE, IN_PUSH },
    [0xE6] = { 8, 2, AM_IMM8, IN_AND }, [0xE7] = { 16, 1, AM_NONE, IN_RST },
    [0xE8] = { 16, 2, AM_S8, IN_ADD }, [0xE9] = { 4, 1, AM_NONE, IN_JP },
    [0xEA] = { 16, 3, AM_IMM16, IN_LD }, [0xEB] = { 0, 0, AM_NONE, IN_NONE }, // Invalid
    [0xEC] = { 0, 0, AM_NONE, IN_NONE }, [0xED] = { 0, 0, AM_NONE, IN_NONE }, // Invalid
    [0xEE] = { 8, 2, AM_IMM8, IN_XOR }, [0xEF] = { 16, 1, AM_NONE, IN_RST },

    // 0xFX
    [0xF0] = { 12, 2, AM_HRAM, IN_LDH }, [0xF1] = { 12, 1, AM_NONE, IN_POP },
    [0xF2] = { 8, 1, AM_NONE, IN_LDH }, [0xF3] = { 4, 1, AM_NONE, IN_DI },
    [0xF4] = { 0, 0, AM_NONE, IN_NONE }, [0xF5] = { 16, 1, AM_NONE, IN_PUSH },
    [0xF6] = { 8, 2, AM_IMM8, IN_OR }, [0xF7] = { 16, 1, AM_NONE, IN_RST },
    [0xF8] = { 12, 2, AM_S8, IN_LD }, [0xF9] = { 8, 1, AM_NONE, IN_LD },
    [0xFA] = { 16, 3, AM_IMM16, IN_LD }, [0xFB] = { 4, 1, AM_NONE, IN_EI },
    [0xFC] = { 0, 0, AM_NONE, IN_NONE }, [0xFD] = { 0, 0, AM_NONE, IN_NONE }, // Invalid
    [0xFE] = { 8, 2, AM_IMM8, IN_CP }, [0xFF] = { 16, 1, AM_NONE, IN_RST }
};

static const instr_t CB_INSTR_LOOKUP[256] = {
    // 0x00 - 0x07: RLC
    [0x00] = { 8, 2, AM_R8, IN_RLC }, [0x06] = { 16, 2, AM_HL_INDIR, IN_RLC },
    // 0x08 - 0x0F: RRC
    [0x08] = { 8, 2, AM_R8, IN_RRC }, [0x0E] = { 16, 2, AM_HL_INDIR, IN_RRC },
    // 0x10 - 0x17: RL
    [0x10] = { 8, 2, AM_R8, IN_RL },  [0x16] = { 16, 2, AM_HL_INDIR, IN_RL },
    // 0x18 - 0x1F: RR
    [0x18] = { 8, 2, AM_R8, IN_RR },  [0x1E] = { 16, 2, AM_HL_INDIR, IN_RR },
    // 0x20 - 0x27: SLA
    [0x20] = { 8, 2, AM_R8, IN_SLA }, [0x26] = { 16, 2, AM_HL_INDIR, IN_SLA },
    // 0x28 - 0x2F: SRA
    [0x28] = { 8, 2, AM_R8, IN_SRA }, [0x2E] = { 16, 2, AM_HL_INDIR, IN_SRA },
    // 0x30 - 0x37: SWAP
    [0x30] = { 8, 2, AM_R8, IN_SWAP },[0x36] = { 16, 2, AM_HL_INDIR, IN_SWAP },
    // 0x38 - 0x3F: SRL
    [0x38] = { 8, 2, AM_R8, IN_SRL }, [0x3E] = { 16, 2, AM_HL_INDIR, IN_SRL },

    // 0x40 - 0x7F: BIT (Testing bits 0-7)
    [0x40] = { 8, 2, AM_R8, IN_BIT }, [0x46] = { 12, 2, AM_HL_INDIR, IN_BIT },
    [0x7F] = { 8, 2, AM_R8, IN_BIT },

    // 0x80 - 0xBF: RES (Resetting bits 0-7)
    [0x80] = { 8, 2, AM_R8, IN_RES }, [0x86] = { 16, 2, AM_HL_INDIR, IN_RES },
    
    // 0xC0 - 0xFF: SET (Setting bits 0-7)
    [0xC0] = { 8, 2, AM_R8, IN_SET }, [0xC6] = { 16, 2, AM_HL_INDIR, IN_SET }
};

instr_t parse_instr(byte opcode){
    if(opcode >= 256) {
        ERROR("Opcode out of range!");
    }

    if(opcode == 0xCB) {
        return CB_INSTR_LOOKUP[opcode];
    }
    else {
        return INSTR_LOOKUP[opcode];
    }
}