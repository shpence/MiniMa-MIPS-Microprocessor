#pragma once
#include <stdint.h>
#include "Instruction.h"
#include "ArrayList.h"

/* Returns a list of copies of the Instructions with the
 * immediate field (i-type) or jump_address (j-type) of the instruction filled in
 * with the address calculated from the branch_label.
 *
 * The instruction should not be changed if it is not a branch or jump instruction.
 *
 * unresolved: input program, whose branch/jump instructions don't have resolved immediate/jump_address
 * first_pc: address where the first instruction of the program will eventually be placed in memory
 * resolved: after the function returns, resolved contains the resulting instructions
 */
void resolve_addresses(struct ArrayList *unresolved, uint32_t first_pc, struct ArrayList *resolved);
