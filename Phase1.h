#pragma once
#include "ArrayList.h"

/* Translates the MAL instruction to 1-3 TAL instructions
 * and returns the TAL instructions in a list
 *
 * mals: input program as a list of Instruction objects
 * tals: after the function returns, will contain TAL instructions (should be same size or longer than input list)
 */
void mal_to_tal(struct ArrayList *mals, struct ArrayList *tals);
