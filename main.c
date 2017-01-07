#include <stdio.h>

#include "CPU.h"

void show_cpu_state(cpu_t *cpu) {
    FILE *out = stdout;

    fprintf(out, "REGISTERS: \n");
    fprintf(out, "A: 0x%02X\n", cpu->registers[REG_A]);
    fprintf(out, "B: 0x%02X\tC: 0x%02X\n", cpu->registers[REG_B], cpu->registers[REG_C]);
    fprintf(out, "D: 0x%02X\tE: 0x%02X\n", cpu->registers[REG_D], cpu->registers[REG_E]);
    fprintf(out, "H: 0x%02X\tL: 0x%02X\n", cpu->registers[REG_H], cpu->registers[REG_L]);
    fprintf(out, "PC: 0x%04X\tSP: 0x%04X\n", cpu->program_counter, cpu->stack_pointer);
    fprintf(out, "Flags: C = %d, P = %d, AC = %d, Z = %d, S = %d\n",
            cpu->flags[CARRY_FLAG],
            cpu->flags[PARITY_FLAG],
            cpu->flags[AUXILIARY_CARRY_FLAG],
            cpu->flags[ZERO_FLAG],
            cpu->flags[SIGN_FLAG]
    );

    fprintf(out, "MEMORY: 0x%02X\n", cpu->memory[0x2010]);
}

int main() {
    uint8_t opcodes[] = {
            0x3E, 0x00, 0xC3, 0x07, 0x10, 0x3E, 0x20, 0x3E, 0xFF, 0x76
    };

    cpu_t cpu = init_cpu(opcodes, sizeof(opcodes) / sizeof(opcodes[0]), 0x1000);
    show_cpu_state(&cpu);
    execute(&cpu);
    show_cpu_state(&cpu);

    return 0;
}
