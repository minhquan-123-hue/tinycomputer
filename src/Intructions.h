#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstdint>

/*
    ============================================================
                        Tiny-8 Instruction Format
    ============================================================

    Every instruction occupies exactly 2 bytes in memory.

        +------------+-------------+
        | Opcode     | Operand     |
        +------------+-------------+
        | 1 byte     | 1 byte      |
        +------------+-------------+

    Byte 0 : Opcode
        Identifies which instruction the CPU executes.

    Byte 1 : Operand
        Meaning depends on the opcode.

        Examples:
            - Memory address
            - Immediate value
            - Unused (0x00)

    Because every instruction is exactly 2 bytes:

        Fetch:
            opcode  = memory[PC]
            operand = memory[PC + 1]

        Normal execution:
            PC += 2

    Some instructions (such as JMP and JZ) overwrite the
    Program Counter instead of allowing the normal PC += 2.
*/

/*
    ============================================================
                           Opcode Table
    ============================================================

    HALT
        Stop CPU execution.

    LOAD
        A = memory[operand]

    STORE
        memory[operand] = A

    MOV_A_B
        B = A

    MOV_B_A
        A = B

    ADD
        A = A + B

    SUB
        A = A - B

    AND_OP
        A = A & B

    OR_OP
        A = A | B

    JMP
        PC = operand

    JZ
        if (ZERO flag)
            PC = operand

    LOAD_IMM
        A = operand
*/

// đây là những lệnh để điều khiển các phần
// của máy tính , và từng lệnh này có thể 
// không thể thay đổi được 
// và kiến trúc máy tính hiện tại chỉ có thể
// thực hiện những lệnh sau.
constexpr uint8_t OPCODE_HALT      = 0x00;
constexpr uint8_t OPCODE_LOAD      = 0x01;
constexpr uint8_t OPCODE_STORE     = 0x02;
constexpr uint8_t OPCODE_MOV_A_B   = 0x03;
constexpr uint8_t OPCODE_MOV_B_A   = 0x04;
constexpr uint8_t OPCODE_ADD       = 0x05;
constexpr uint8_t OPCODE_SUB       = 0x06;
constexpr uint8_t OPCODE_AND_OP    = 0x07;
constexpr uint8_t OPCODE_OR_OP     = 0x08;
constexpr uint8_t OPCODE_JMP       = 0x09;
constexpr uint8_t OPCODE_JZ        = 0x0A;
constexpr uint8_t OPCODE_LOAD_IMM  = 0x0B;

#endif