#pragma once
#include "Instruction.h"
#include "ArrayList.h"

/* Translate each Instruction object into
 * a 32-bit number.
 *
 * tals: list of Instructions to translate
 * machineCode: after the function returns, contains the instructions in 32-bit binary representation
 * 
 */
void translate_instructions(struct ArrayList *tals, uint32_t machineCode[]);
