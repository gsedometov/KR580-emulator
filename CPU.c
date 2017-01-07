//
// Created by yoba on 06.01.17.
//

#include "CPU.h"

cpu_t init_cpu(uint8_t *opcodes, uint16_t size, uint16_t start_address) {
    cpu_t cpu = {};
    int i = 0;
    cpu.memory_pointer = start_address;

    while(cpu.memory_pointer < start_address + size && cpu.memory_pointer < MEMORY_SIZE) {
        cpu.memory[cpu.memory_pointer++] = opcodes[i++];
    }

    cpu.memory_pointer = start_address;
    return cpu;
}

uint16_t concat_numbers(uint8_t arg1, uint8_t arg2) {
    return (arg1 << 8) + arg2;
}

uint16_t get_address_from_registers(cpu_t *cpu, register_t r1, register_t r2) {
    return concat_numbers(cpu->registers[r1], cpu->registers[r2]);
}

void set_flag(cpu_t *cpu, flag_t flag, bool_t value) {
    cpu->flags[flag] = value;
}

void push_stack(cpu_t *cpu, uint8_t value) {
    if (cpu->stack_pointer++ < STACK_SIZE)
        cpu->stack[cpu->stack_pointer] = value;
}

uint8_t pop_stack(cpu_t *cpu) {
    return cpu->stack[cpu->stack_pointer--];
}

int execute_command(cpu_t *cpu, code_t command) {
    uint16_t b_address = get_address_from_registers(cpu, REG_C, REG_B);
    uint16_t d_address = get_address_from_registers(cpu, REG_E, REG_D);
    uint16_t h_address = get_address_from_registers(cpu, REG_L, REG_H);
    uint8_t  next_byte = cpu->memory[cpu->memory_pointer + 1];

    switch (command) {
        case ADD_A:
            cpu->registers[REG_A] += cpu->registers[REG_A];
            break;
        case ADD_B:
            cpu->registers[REG_A] += cpu->registers[REG_B];
            break;
        case ADD_C:
            cpu->registers[REG_A] += cpu->registers[REG_C];
            break;
        case ADD_D:
            cpu->registers[REG_A] += cpu->registers[REG_D];
            break;
        case ADD_E:
            cpu->registers[REG_A] += cpu->registers[REG_E];
            break;
        case ADD_H:
            cpu->registers[REG_A] += cpu->registers[REG_H];
            break;
        case ADD_L:
            cpu->registers[REG_A] += cpu->registers[REG_L];
            break;
        case ADD_M:
            cpu->registers[REG_A] += cpu->memory[h_address];
            break;
        case ADI_D8:
            cpu->registers[REG_A] += cpu->memory[++cpu->memory_pointer];
            break;
        case ADC_A:
            cpu->registers[REG_A] += cpu->registers[REG_A] + cpu->flags[CARRY_FLAG];
            break;
        case ADC_B:
            cpu->registers[REG_A] += cpu->registers[REG_B] + cpu->flags[CARRY_FLAG];
            break;
        case ADC_C:
            cpu->registers[REG_A] += cpu->registers[REG_C] + cpu->flags[CARRY_FLAG];
            break;
        case ADC_D:
            cpu->registers[REG_A] += cpu->registers[REG_D] + cpu->flags[CARRY_FLAG];
            break;
        case ADC_E:
            cpu->registers[REG_A] += cpu->registers[REG_E] + cpu->flags[CARRY_FLAG];
            break;
        case ADC_H:
            cpu->registers[REG_A] += cpu->registers[REG_H] + cpu->flags[CARRY_FLAG];
            break;
        case ADC_L:
            cpu->registers[REG_A] += cpu->registers[REG_L] + cpu->flags[CARRY_FLAG];
            break;
        case ADC_M:
            cpu->registers[REG_A] += cpu->memory[h_address] + cpu->flags[CARRY_FLAG];
            break;
        case ACI_D8:
            cpu->registers[REG_A] += cpu->memory[++cpu->memory_pointer] + cpu->flags[CARRY_FLAG];
            break;
        case ANA_A:
            cpu->registers[REG_A] &= cpu->registers[REG_A];
            break;
        case ANA_B:
            cpu->registers[REG_A] &= cpu->registers[REG_B];
            break;
        case ANA_C:
            cpu->registers[REG_A] &= cpu->registers[REG_C];
            break;
        case ANA_D:
            cpu->registers[REG_A] &= cpu->registers[REG_D];
            break;
        case ANA_E:
            cpu->registers[REG_A] &= cpu->registers[REG_E];
            break;
        case ANA_H:
            cpu->registers[REG_A] &= cpu->registers[REG_H];
            break;
        case ANA_L:
            cpu->registers[REG_A] &= cpu->registers[REG_L];
            break;
        case ANA_M:
            cpu->registers[REG_A] &= cpu->memory[h_address];
            break;
        case ANI_D8:
            cpu->registers[REG_A] &= cpu->memory[++cpu->memory_pointer];
            break;
        case CALL_A16:break;
        case CZ_A16:break;
        case CNZ_A16:break;
        case CP_A16:break;
        case CM_A16:break;
        case CC_A16:break;
        case CNC_A16:break;
        case CPE_A16:break;
        case CPO_A16:break;
        case CMA:
            cpu->registers[REG_A] = ~cpu->registers[REG_A];
            break;
        case CMC:
            cpu->flags[CARRY_FLAG] = ~cpu->flags[CARRY_FLAG];
            break;
        case CMP_A:
            set_flag(cpu, ZERO_FLAG, true);
            break;
        case CMP_B:
            set_flag(cpu, ZERO_FLAG, (bool_t) (cpu->registers[REG_B] - cpu->registers[REG_A]));
            break;
        case CMP_C:
            set_flag(cpu, ZERO_FLAG, (bool_t) (cpu->registers[REG_C] - cpu->registers[REG_A]));
            break;
        case CMP_D:
            set_flag(cpu, ZERO_FLAG, (bool_t) (cpu->registers[REG_D] - cpu->registers[REG_A]));
            break;
        case CMP_E:
            set_flag(cpu, ZERO_FLAG, (bool_t) (cpu->registers[REG_C] - cpu->registers[REG_A]));
            break;
        case CMP_H:
            set_flag(cpu, ZERO_FLAG, (bool_t) (cpu->registers[REG_H] - cpu->registers[REG_A]));
            break;
        case CMP_L:
            set_flag(cpu, ZERO_FLAG, (bool_t) (cpu->registers[REG_L] - cpu->registers[REG_A]));
            break;
        case CMP_M:
            set_flag(cpu, ZERO_FLAG, (bool_t) (cpu->memory[h_address] - cpu->registers[REG_A]));
            break;
        case CPI_D8:
            set_flag(cpu, ZERO_FLAG, (bool_t) (cpu->memory[++cpu->memory_pointer] - cpu->registers[REG_A]));
            break;
        case DAA:break;
        case DAD_B:
            b_address += h_address;
            break;
        case DAD_D:
            d_address += h_address;
            break;
        case DAD_H:
            h_address += h_address;
            break;
        case DAD_SP:
            cpu->stack_pointer += h_address;
            break;
        case DCR_A:
            cpu->registers[REG_A]--;
            break;
        case DCR_B:
            cpu->registers[REG_B]--;
            break;
        case DCR_C:
            cpu->registers[REG_C]--;
            break;
        case DCR_D:
            cpu->registers[REG_D]--;
            break;
        case DCR_E:
            cpu->registers[REG_E]--;
            break;
        case DCR_H:
            cpu->registers[REG_H]--;
            break;
        case DCR_L:
            cpu->registers[REG_L]--;
            break;
        case DCR_M:
            cpu->memory[h_address]--;
            break;
        case DCX_B:
            b_address--;
            break;
        case DCX_D:
            d_address--;
            break;
        case DCX_H:
            h_address--;
            break;
        case DCX_SP:
            cpu->stack_pointer--;
            break;
        case DI:
            cpu->interrupts_enabled = false;
            break;
        case EI:
            cpu->interrupts_enabled = true;
            break;
        case IN_PP:break;
        case INR_A:
            cpu->registers[REG_A]++;
            break;
        case INR_B:
            cpu->registers[REG_B]++;
            break;
        case INR_C:
            cpu->registers[REG_C]++;
            break;
        case INR_D:
            cpu->registers[REG_D]++;
            break;
        case INR_E:
            cpu->registers[REG_E]++;
            break;
        case INR_H:
            cpu->registers[REG_H]++;
            break;
        case INR_L:
            cpu->registers[REG_L]++;
            break;
        case INR_M:
            cpu->memory[h_address]++;
            break;
        case INX_B:
            b_address++;
            break;
        case INX_D:
            d_address++;
            break;
        case INX_H:
            h_address++;
            break;
        case INX_SP:
            cpu->stack_pointer++;
            break;
        case JMP_A16:
            cpu->memory_pointer = concat_numbers(cpu->memory[cpu->memory_pointer + 2], cpu->memory[cpu->memory_pointer + 1]) - 1;
            break;
        case JZ_A16:
            if (cpu->flags[ZERO_FLAG])
                cpu->memory_pointer = concat_numbers(cpu->memory[cpu->memory_pointer + 2], cpu->memory[cpu->memory_pointer + 1]) - 1;
            break;
        case JNZ_A16:
            if (!cpu->flags[ZERO_FLAG])
                cpu->memory_pointer = concat_numbers(cpu->memory[cpu->memory_pointer + 2], cpu->memory[cpu->memory_pointer + 1]) - 1;
            break;
        case JP_A16:break;
        case JM_A16:break;
        case JC_A16:
            if (cpu->flags[CARRY_FLAG])
                cpu->memory_pointer = concat_numbers(cpu->memory[cpu->memory_pointer + 2], cpu->memory[cpu->memory_pointer + 1]) - 1;
            break;
        case JNC_A16:
            if (!cpu->flags[CARRY_FLAG])
                cpu->memory_pointer = concat_numbers(cpu->memory[cpu->memory_pointer + 2], cpu->memory[cpu->memory_pointer + 1]) - 1;
            break;
        case JPE_A16:
            if (cpu->flags[PARITY_FLAG])
                cpu->memory_pointer = concat_numbers(cpu->memory[cpu->memory_pointer + 2], cpu->memory[cpu->memory_pointer + 1]) - 1;
            break;
        case JPO_A16:
            if (!cpu->flags[PARITY_FLAG])
                cpu->memory_pointer = concat_numbers(cpu->memory[cpu->memory_pointer + 2], cpu->memory[cpu->memory_pointer + 1]) - 1;
            break;
        case LDA_A16:
            cpu->registers[REG_A] = cpu->memory[concat_numbers(cpu->memory[++cpu->memory_pointer], cpu->memory[++cpu->memory_pointer])];
            break;
        case LDAX_B:
            cpu->registers[REG_A] = cpu->memory[b_address];
            break;
        case LDAX_D:
            cpu->registers[REG_A] = cpu->memory[d_address];
            break;
        case LHLD_A16:
            cpu->registers[REG_L] = (uint8_t) (cpu->memory[h_address] & 0xFF);
            cpu->registers[REG_H] = (uint8_t) (cpu->memory[h_address] >> 8);
            break;
        case LXI_B_D16:
            cpu->registers[REG_C] = cpu->memory[++cpu->memory_pointer];
            cpu->registers[REG_B] = cpu->memory[++cpu->memory_pointer];
            break;
        case LXI_H_D16:
            cpu->registers[REG_L] = cpu->memory[++cpu->memory_pointer];
            cpu->registers[REG_H] = cpu->memory[++cpu->memory_pointer];
            break;
        case LXI_SP_D16:
            cpu->stack_pointer = concat_numbers(cpu->memory[++cpu->memory_pointer], cpu->memory[++cpu->memory_pointer]);
            break;
        case MOV_A_A:
            cpu->registers[REG_A] = cpu->registers[REG_A];
            break;
        case MOV_A_B:
            cpu->registers[REG_A] = cpu->registers[REG_B];
            break;
        case MOV_A_C:
            cpu->registers[REG_A] = cpu->registers[REG_C];
            break;
        case MOV_A_D:
            cpu->registers[REG_A] = cpu->registers[REG_D];
            break;
        case MOV_A_E:
            cpu->registers[REG_A] = cpu->registers[REG_E];
            break;
        case MOV_A_H:
            cpu->registers[REG_A] = cpu->registers[REG_H];
            break;
        case MOV_A_L:
            cpu->registers[REG_A] = cpu->registers[REG_L];
            break;
        case MOV_A_M:
            cpu->registers[REG_A] = cpu->memory[h_address];
            break;
        case MOV_B_A:
            cpu->registers[REG_B] = cpu->registers[REG_A];
            break;
        case MOV_B_B:
            cpu->registers[REG_B] = cpu->registers[REG_B];
            break;
        case MOV_B_C:
            cpu->registers[REG_B] = cpu->registers[REG_C];
            break;
        case MOV_B_D:
            cpu->registers[REG_B] = cpu->registers[REG_D];
            break;
        case MOV_B_E:
            cpu->registers[REG_B] = cpu->registers[REG_E];
            break;
        case MOV_B_H:
            cpu->registers[REG_B] = cpu->registers[REG_H];
            break;
        case MOV_B_L:
            cpu->registers[REG_B] = cpu->registers[REG_L];
            break;
        case MOV_B_M:
            cpu->registers[REG_B] = cpu->memory[h_address];
            break;
        case MOV_C_A:
            cpu->registers[REG_C] = cpu->registers[REG_A];
            break;
        case MOV_C_B:
            cpu->registers[REG_C] = cpu->registers[REG_B];
            break;
        case MOV_C_C:
            cpu->registers[REG_C] = cpu->registers[REG_C];
            break;
        case MOV_C_D:
            cpu->registers[REG_C] = cpu->registers[REG_D];
            break;
        case MOV_C_E:
            cpu->registers[REG_C] = cpu->registers[REG_E];
            break;
        case MOV_C_H:
            cpu->registers[REG_C] = cpu->registers[REG_H];
            break;
        case MOV_C_L:
            cpu->registers[REG_C] = cpu->registers[REG_L];
            break;
        case MOV_C_M:
            cpu->registers[REG_C] = cpu->memory[h_address];
            break;
        case MOV_D_A:
            cpu->registers[REG_D] = cpu->registers[REG_A];
            break;
        case MOV_D_B:
            cpu->registers[REG_D] = cpu->registers[REG_B];
            break;
        case MOV_D_C:
            cpu->registers[REG_D] = cpu->registers[REG_C];
            break;
        case MOV_D_D:
            cpu->registers[REG_D] = cpu->registers[REG_D];
            break;
        case MOV_D_E:
            cpu->registers[REG_D] = cpu->registers[REG_E];
            break;
        case MOV_D_H:
            cpu->registers[REG_D] = cpu->registers[REG_H];
            break;
        case MOV_D_L:
            cpu->registers[REG_D] = cpu->registers[REG_L];
            break;
        case MOV_D_M:
            cpu->registers[REG_D] = cpu->memory[h_address];
            break;
        case MOV_E_A:
            cpu->registers[REG_E] = cpu->registers[REG_A];
            break;
        case MOV_E_B:
            cpu->registers[REG_E] = cpu->registers[REG_B];
            break;
        case MOV_E_C:
            cpu->registers[REG_E] = cpu->registers[REG_C];
            break;
        case MOV_E_D:
            cpu->registers[REG_E] = cpu->registers[REG_D];
            break;
        case MOV_E_E:
            cpu->registers[REG_E] = cpu->registers[REG_E];
            break;
        case MOV_E_H:
            cpu->registers[REG_E] = cpu->registers[REG_H];
            break;
        case MOV_E_L:
            cpu->registers[REG_E] = cpu->registers[REG_L];
            break;
        case MOV_E_M:
            cpu->registers[REG_E] = cpu->memory[h_address];
            break;
        case MOV_H_A:
            cpu->registers[REG_H] = cpu->registers[REG_A];
            break;
        case MOV_H_B:
            cpu->registers[REG_H] = cpu->registers[REG_B];
            break;
        case MOV_H_C:
            cpu->registers[REG_H] = cpu->registers[REG_C];
            break;
        case MOV_H_D:
            cpu->registers[REG_H] = cpu->registers[REG_D];
            break;
        case MOV_H_E:
            cpu->registers[REG_H] = cpu->registers[REG_E];
            break;
        case MOV_H_H:
            cpu->registers[REG_H] = cpu->registers[REG_H];
            break;
        case MOV_H_L:
            cpu->registers[REG_H] = cpu->registers[REG_L];
            break;
        case MOV_H_M:
            cpu->registers[REG_H] = cpu->memory[h_address];
            break;
        case MOV_L_A:
            cpu->registers[REG_L] = cpu->registers[REG_A];
            break;
        case MOV_L_B:
            cpu->registers[REG_L] = cpu->registers[REG_B];
            break;
        case MOV_L_C:
            cpu->registers[REG_L] = cpu->registers[REG_C];
            break;
        case MOV_L_D:
            cpu->registers[REG_L] = cpu->registers[REG_D];
            break;
        case MOV_L_E:
            cpu->registers[REG_L] = cpu->registers[REG_E];
            break;
        case MOV_L_H:
            cpu->registers[REG_L] = cpu->registers[REG_H];
            break;
        case MOV_L_L:
            cpu->registers[REG_L] = cpu->registers[REG_L];
            break;
        case MOV_L_M:
            cpu->registers[REG_L] = cpu->memory[h_address];
            break;
        case MOV_M_A:
            cpu->memory[h_address] = cpu->registers[REG_A];
            break;
        case MOV_M_B:
            cpu->memory[h_address] = cpu->registers[REG_B];
            break;
        case MOV_M_C:
            cpu->memory[h_address] = cpu->registers[REG_C];
            break;
        case MOV_M_D:
            cpu->memory[h_address] = cpu->registers[REG_D];
            break;
        case MOV_M_E:
            cpu->memory[h_address] = cpu->registers[REG_E];
            break;
        case MOV_M_H:
            cpu->memory[h_address] = cpu->registers[REG_H];
            break;
        case MOV_M_L:
            cpu->memory[h_address] = cpu->registers[REG_L];
            break;
        case MVI_A_D8:
            cpu->registers[REG_A] = cpu->memory[++cpu->memory_pointer];
            break;
        case MVI_B_D8:
            cpu->registers[REG_B] = cpu->memory[++cpu->memory_pointer];
            break;
        case MVI_C_D8:
            cpu->registers[REG_C] = cpu->memory[++cpu->memory_pointer];
            break;
        case MVI_D_D8:
            cpu->registers[REG_D] = cpu->memory[++cpu->memory_pointer];
            break;
        case MVI_E_D8:
            cpu->registers[REG_E] = cpu->memory[++cpu->memory_pointer];
            break;
        case MVI_H_D8:
            cpu->registers[REG_H] = cpu->memory[++cpu->memory_pointer];
            break;
        case MVI_L_D8:
            cpu->registers[REG_L] = cpu->memory[++cpu->memory_pointer];
            break;
        case MVI_M_D8:
            cpu->memory[h_address] = cpu->memory[++cpu->memory_pointer];
            break;
        case ORA_A:
            cpu->registers[REG_A] |= cpu->registers[REG_A];
            break;
        case ORA_B:
            cpu->registers[REG_A] |= cpu->registers[REG_B];
            break;
        case ORA_C:
            cpu->registers[REG_A] |= cpu->registers[REG_C];
            break;
        case ORA_D:
            cpu->registers[REG_A] |= cpu->registers[REG_D];
            break;
        case ORA_E:
            cpu->registers[REG_A] |= cpu->registers[REG_E];
            break;
        case ORA_H:
            cpu->registers[REG_A] |= cpu->registers[REG_H];
            break;
        case ORA_L:
            cpu->registers[REG_A] |= cpu->registers[REG_L];
            break;
        case ORA_M:
            cpu->registers[REG_A] |= cpu->memory[h_address];
            break;
        case ORI_D8:
            cpu->registers[REG_A] |= cpu->memory[++cpu->memory_pointer];
            break;
        case OUT_PP:break;
        case PCHL:break;
        case POP_B:break;
        case POP_D:break;
        case POP_H:break;
        case POP_PSW:break;
        case PUSH_B:break;
        case PUSH_D:break;
        case PUSH_H:break;
        case PUSH_PSW:break;
        case RAL:break;
        case RAR:break;
        case RLC:break;
        case RRC:break;
        case RIM:break;
        case RET:break;
        case RZ:break;
        case RNZ:break;
        case RP:break;
        case RM:break;
        case RC:break;
        case RNC:break;
        case RPE:break;
        case RPO:break;
        case RST_0:break;
        case RST_1:break;
        case RST_2:break;
        case RST_3:break;
        case RST_4:break;
        case RST_5:break;
        case RST_6:break;
        case RST_7:break;
        case SIM:break;
        case SPHL:
            cpu->stack_pointer = h_address;
            break;
        case SHLD_A16:
            cpu->memory[++cpu->memory_pointer] = cpu->registers[REG_L];
            cpu->memory[++cpu->memory_pointer] = cpu->registers[REG_H];
            break;
        case STA_A16:
            cpu->memory[concat_numbers(cpu->memory[++cpu->memory_pointer], cpu->memory[++cpu->memory_pointer])] = cpu->registers[REG_A];
            break;
        case STAX_B:
            cpu->memory[b_address] = cpu->registers[REG_A];
            break;
        case STAX_D:
            cpu->memory[d_address] = cpu->registers[REG_A];
            break;
        case STC:
            set_flag(cpu, CARRY_FLAG, true);
            break;
        case SUB_A:
            cpu->registers[REG_A] -= cpu->registers[REG_A];
            break;
        case SUB_B:
            cpu->registers[REG_A] -= cpu->registers[REG_B];
            break;
        case SUB_C:
            cpu->registers[REG_A] -= cpu->registers[REG_C];
            break;
        case SUB_D:
            cpu->registers[REG_A] -= cpu->registers[REG_D];
            break;
        case SUB_E:
            cpu->registers[REG_A] -= cpu->registers[REG_E];
            break;
        case SUB_H:
            cpu->registers[REG_A] -= cpu->registers[REG_H];
            break;
        case SUB_L:
            cpu->registers[REG_A] -= cpu->registers[REG_E];
            break;
        case SUB_M:
            cpu->registers[REG_A] -= cpu->memory[h_address];
            break;
        case SUI_D8:
            cpu->registers[REG_A] -= cpu->memory[++cpu->memory_pointer];
            break;
        case SBB_A:break;
        case SBB_B:break;
        case SBB_C:break;
        case SBB_D:break;
        case SBB_E:break;
        case SBB_H:break;
        case SBB_L:break;
        case SBB_M:break;
        case SBI_D8:break;
        case XCHG:
            push_stack(cpu, cpu->registers[REG_E]);
            push_stack(cpu, cpu->registers[REG_D]);
            cpu->registers[REG_E] = cpu->registers[REG_L];
            cpu->registers[REG_D] = cpu->registers[REG_H];
            cpu->registers[REG_L] = pop_stack(cpu);
            cpu->registers[REG_H] = pop_stack(cpu);
            break;
        case XTHL:break;
        case XRA_A:
            cpu->registers[REG_A] ^= cpu->registers[REG_A];
            break;
        case XRA_B:
            cpu->registers[REG_A] ^= cpu->registers[REG_B];
            break;
        case XRA_C:
            cpu->registers[REG_A] ^= cpu->registers[REG_C];
            break;
        case XRA_D:
            cpu->registers[REG_A] ^= cpu->registers[REG_D];
            break;
        case XRA_E:
            cpu->registers[REG_A] ^= cpu->registers[REG_E];
            break;
        case XRA_H:
            cpu->registers[REG_A] ^= cpu->registers[REG_H];
            break;
        case XRA_L:
            cpu->registers[REG_A] ^= cpu->registers[REG_L];
            break;
        case XRA_M:
            cpu->registers[REG_A] ^= cpu->memory[h_address];
            break;
        case XRI_D8:
            cpu->registers[REG_A] ^= cpu->memory[++cpu->memory_pointer];
            break;
        case NOP:
        case HLT:
            return 0;
    }

    cpu->program_counter = cpu->memory_pointer++;
    return 0;
}

int execute(cpu_t *cpu) {
    while (cpu->memory[cpu->memory_pointer] != HLT && cpu->memory_pointer < MEMORY_SIZE) {
        execute_command(cpu, (code_t) cpu->memory[cpu->memory_pointer]);
    }

    return 0;
}
