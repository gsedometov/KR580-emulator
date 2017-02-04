//
// Created by yoba on 06.01.17.
//

#ifndef EMULATOR_CPU_H
#define EMULATOR_CPU_H

#include <stdint.h>
#include <stdbool.h>

#define REGISTERS_COUNT 0x8
#define MEMORY_SIZE 0xFFFF
#define STACK_SIZE 0xFFFF
#define FLAGS_COUNT 0x5

typedef enum {
    ADD_A = 0x87,
    ADD_B = 0x80,
    ADD_C = 0x81,
    ADD_D = 0x82,
    ADD_E = 0x83,
    ADD_H = 0x84,
    ADD_L = 0x85,
    ADD_M = 0x86,
    ADI_D8 = 0xC6,
    ADC_A = 0x8F,
    ADC_B = 0x88,
    ADC_C = 0x89,
    ADC_D = 0x8A,
    ADC_E = 0x8B,
    ADC_H = 0x8C,
    ADC_L = 0x8D,
    ADC_M = 0x8E,
    ACI_D8 = 0xCE,
    ANA_A = 0xA7,
    ANA_B = 0xA0,
    ANA_C = 0xA1,
    ANA_D = 0xA2,
    ANA_E = 0xA3,
    ANA_H = 0xA4,
    ANA_L = 0xA5,
    ANA_M = 0xA6,
    ANI_D8 = 0xE6,
    CALL_A16 = 0xCD,
    CZ_A16 = 0xCC,
    CNZ_A16 = 0xC4,
    CP_A16 = 0xF4,
    CM_A16 = 0xFC,
    CC_A16 = 0xDC,
    CNC_A16 = 0xD4,
    CPE_A16 = 0xEC,
    CPO_A16 = 0xE4,
    CMA = 0x2F,
    CMC = 0x3F,
    CMP_A = 0xBF,
    CMP_B = 0xB8,
    CMP_C = 0xB9,
    CMP_D = 0xBA,
    CMP_E = 0xBB,
    CMP_H = 0xBC,
    CMP_L = 0xBD,
    CMP_M = 0xBE,
    CPI_D8 = 0xFE,
    DAA = 0x27,
    DAD_B = 0x09,
    DAD_D = 0x19,
    DAD_H = 0x29,
    DAD_SP = 0x39,
    DCR_A = 0x3D,
    DCR_B = 0x05,
    DCR_C = 0x0D,
    DCR_D = 0x15,
    DCR_E = 0x1D,
    DCR_H = 0x25,
    DCR_L = 0x2D,
    DCR_M = 0x35,
    DCX_B = 0x0B,
    DCX_D = 0x1B,
    DCX_H = 0x2B,
    DCX_SP = 0x3B,
    DI = 0xF3,
    EI = 0xFB,
    HLT = 0x76,
    IN_PP = 0xDB,
    INR_A = 0x3C,
    INR_B = 0x04,
    INR_C = 0x0C,
    INR_D = 0x14,
    INR_E = 0x1C,
    INR_H = 0x24,
    INR_L = 0x2C,
    INR_M = 0x34,
    INX_B = 0x03,
    INX_D = 0x13,
    INX_H = 0x23,
    INX_SP = 0x33,
    JMP_A16 = 0xC3,
    JZ_A16 = 0xCA,
    JNZ_A16 = 0xC2,
    JP_A16 = 0xF2,
    JM_A16 = 0xFA,
    JC_A16 = 0xDA,
    JNC_A16 = 0xD2,
    JPE_A16 = 0xEA,
    JPO_A16 = 0xE2,
    LDA_A16 = 0x3A,
    LDAX_B = 0x0A,
    LDAX_D = 0x1A,
    LHLD_A16 = 0x2A,
    LXI_B_D16 = 0x01,
    LXI_H_D16 = 0x21,
    LXI_SP_D16 = 0x31,
    MOV_A_A = 0x7F,
    MOV_A_B = 0x78,
    MOV_A_C = 0x79,
    MOV_A_D = 0x7A,
    MOV_A_E = 0x7B,
    MOV_A_H = 0x7C,
    MOV_A_L = 0x7D,
    MOV_A_M = 0x7E,
    MOV_B_A = 0x47,
    MOV_B_B = 0x40,
    MOV_B_C = 0x41,
    MOV_B_D = 0x42,
    MOV_B_E = 0x43,
    MOV_B_H = 0x44,
    MOV_B_L = 0x45,
    MOV_B_M = 0x46,
    MOV_C_A = 0x4F,
    MOV_C_B = 0x48,
    MOV_C_C = 0x49,
    MOV_C_D = 0x4A,
    MOV_C_E = 0x4B,
    MOV_C_H = 0x4C,
    MOV_C_L = 0x4D,
    MOV_C_M = 0x4E,
    MOV_D_A = 0x57,
    MOV_D_B = 0x50,
    MOV_D_C = 0x51,
    MOV_D_D = 0x52,
    MOV_D_E = 0x53,
    MOV_D_H = 0x54,
    MOV_D_L = 0x55,
    MOV_D_M = 0x56,
    MOV_E_A = 0x5F,
    MOV_E_B = 0x58,
    MOV_E_C = 0x59,
    MOV_E_D = 0x5A,
    MOV_E_E = 0x5B,
    MOV_E_H = 0x5C,
    MOV_E_L = 0x5D,
    MOV_E_M = 0x5E,
    MOV_H_A = 0x67,
    MOV_H_B = 0x60,
    MOV_H_C = 0x61,
    MOV_H_D = 0x62,
    MOV_H_E = 0x63,
    MOV_H_H = 0x64,
    MOV_H_L = 0x65,
    MOV_H_M = 0x66,
    MOV_L_A = 0x6F,
    MOV_L_B = 0x68,
    MOV_L_C = 0x69,
    MOV_L_D = 0x6A,
    MOV_L_E = 0x6B,
    MOV_L_H = 0x6C,
    MOV_L_L = 0x6D,
    MOV_L_M = 0x6E,
    MOV_M_A = 0x77,
    MOV_M_B = 0x70,
    MOV_M_C = 0x71,
    MOV_M_D = 0x72,
    MOV_M_E = 0x73,
    MOV_M_H = 0x74,
    MOV_M_L = 0x75,
    MVI_A_D8 = 0x3E,
    MVI_B_D8 = 0x06,
    MVI_C_D8 = 0x0E,
    MVI_D_D8 = 0x16,
    MVI_E_D8 = 0x1E,
    MVI_H_D8 = 0x26,
    MVI_L_D8 = 0x2E,
    MVI_M_D8 = 0x36,
    NOP = 0x00,
    ORA_A = 0xB7,
    ORA_B = 0xB0,
    ORA_C = 0xB1,
    ORA_D = 0xB2,
    ORA_E = 0xB3,
    ORA_H = 0xB4,
    ORA_L = 0xB5,
    ORA_M = 0xB6,
    ORI_D8 = 0xF6,
    OUT_PP = 0xD3,
    PCHL = 0xE9,
    POP_B = 0xC1,
    POP_D = 0xD1,
    POP_H = 0xE1,
    POP_PSW = 0xF1,
    PUSH_B = 0xC5,
    PUSH_D = 0xD5,
    PUSH_H = 0xE5,
    PUSH_PSW = 0xF5,
    RAL = 0x17,
    RAR = 0x1F,
    RLC = 0x07,
    RRC = 0x0F,
    RIM = 0x20,
    RET = 0xC9,
    RZ = 0xC8,
    RNZ = 0xC0,
    RP = 0xF0,
    RM = 0xF8,
    RC = 0xD8,
    RNC = 0xD0,
    RPE = 0xE8,
    RPO = 0xE0,
    RST_0 = 0xC7,
    RST_1 = 0xCF,
    RST_2 = 0xD7,
    RST_3 = 0xDF,
    RST_4 = 0xE7,
    RST_5 = 0xEF,
    RST_6 = 0xF7,
    RST_7 = 0xFF,
    SIM = 0x30,
    SPHL = 0xF9,
    SHLD_A16 = 0x22,
    STA_A16 = 0x32,
    STAX_B = 0x02,
    STAX_D = 0x12,
    STC = 0x37,
    SUB_A = 0x97,
    SUB_B = 0x90,
    SUB_C = 0x91,
    SUB_D = 0x92,
    SUB_E = 0x93,
    SUB_H = 0x94,
    SUB_L = 0x95,
    SUB_M = 0x96,
    SUI_D8 = 0xD6,
    SBB_A = 0x9F,
    SBB_B = 0x98,
    SBB_C = 0x99,
    SBB_D = 0x9A,
    SBB_E = 0x9B,
    SBB_H = 0x9C,
    SBB_L = 0x9D,
    SBB_M = 0x9E,
    SBI_D8 = 0xDE,
    XCHG = 0xEB,
    XTHL = 0xE3,
    XRA_A = 0xAF,
    XRA_B = 0xA8,
    XRA_C = 0xA9,
    XRA_D = 0xAA,
    XRA_E = 0xAB,
    XRA_H = 0xAC,
    XRA_L = 0xAD,
    XRA_M = 0xAE,
    XRI_D8 = 0xEE
} code_t;

typedef enum {
    REG_A = 0,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L
} register_t;

typedef enum {
    CARRY_FLAG = 0,
    PARITY_FLAG,
    AUXILIARY_CARRY_FLAG,
    ZERO_FLAG,
    SIGN_FLAG
} flag_t;

// typedef enum { false = 0, true } bool;

typedef struct {
    uint8_t registers[REGISTERS_COUNT];
    bool flags[FLAGS_COUNT];
    uint8_t memory[MEMORY_SIZE];
    uint8_t stack[STACK_SIZE];
    uint16_t program_counter;
    uint16_t stack_pointer;
    uint32_t tick_counter;

    uint16_t memory_pointer;
    bool interrupts_enabled;
} cpu_t;

cpu_t init_cpu(uint8_t *opcodes, uint16_t size, uint16_t start_address);
int execute_command(cpu_t *cpu, code_t command);
int execute(cpu_t *cpu);

#endif //EMULATOR_CPU_H
