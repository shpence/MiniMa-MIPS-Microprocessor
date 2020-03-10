#pragma once

#include <stdint.h>
#include <stdbool.h>

enum ID{
        //R-Type
        sll,
        /*
        srl,
        sra,
        sllv,
        srlv,
        srav,
        jr,
        jalr,
        mfhi,
        mthi,
        mflo,
        mtlo,
        mult,
        multu,
        div,
        divu,
        add,
        */
        addu,
        /*
        sub,
        subu,
        and,
        */
        or,
        /*
        xor,
        nor,
        */
        slt,
        /*
        sltu,
        //J-Type
        j,
        jal,
        */
        //I-Type
        beq,
        bne,
        /*
        blez,
        bgtz,*/
        addi,
        addiu,
        /*
        slti,
        sltiu,
        andi,
        */
        ori,
        /*
        xori,
        */
        lui,
        /*
        lb,
        lh,
        lw,
        lbu,
        lhu,
        sb,
        sh,
        sw,
        */
        
        //the following IDs are psuedo instructions
        blt,
        bge,
        /*
        bgt,
        ble,
        */
        mov,
        /*
        li,
        la,
        */
};

#define MAX_LABEL_LENGTH 64

// represents a MAL instruction
// you may use this to represent TAL instructions, too
// not all fields will always be used
struct Instruction {
    enum ID instruction_id;   // id indicating the instruction
    uint8_t rd;            // register number destination
    uint8_t rs;            // register number source
    uint8_t rt;            // register number secondary source
    int32_t immediate;     // immediate, may use up to 32 bits
    uint32_t jump_address;  // jump address  
    uint8_t shift_amount;  // shift amount 
    char label[MAX_LABEL_LENGTH]; // label of the line this Instruction appears on
    char branch_label[MAX_LABEL_LENGTH];  // label used by branch or jump instructions
};

void toString(struct Instruction this, char *result);

bool equal(struct Instruction a, struct Instruction b);

struct Instruction newInstructionBlank();

struct Instruction newInstruction(enum ID instruction_id, uint8_t rd, uint8_t rs, uint8_t rt, int32_t immediate, uint32_t jump_address, uint8_t shift_amount, char *label, char *branch_label);
