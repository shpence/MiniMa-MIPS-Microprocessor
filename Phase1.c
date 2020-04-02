#include "Phase1.h"

void mal_to_tal(struct ArrayList *mals, struct ArrayList *tals) {
	for (int i = 0; i < mals->size; i++) {
		enum ID id = get(mals,i).instruction_id; // get the id number at the start of the loop

		// instruction is addiu
		if (id == 7 && get(mals, i).immediate >= 2^16) {	
			struct Instruction inst;
			int shifted = get(mals, i).immediate >> 16; // upper 16 bits of the immediate
			inst = newInstruction(lui, 0, 0, 1, shifted, 0, 0, "", "");
			addLast(tals, inst);

			shifted = get(mals, i).immediate << 16;
			shifted = shifted >> 16;
			inst = newInstruction(ori, 0, 1, 1, shifted, 0, 0, "", "");
			addLast(tals, inst);

			inst = newInstruction(addu, get(mals, i).rd, get(mals, i).rs, 1, 0, 0, 0, "", "");
			addLast(tals, inst);
		}

		// instruction is ori
		else if (id == 8 && get(mals, i).immediate >= 2^16) {
			struct Instruction inst;
			int shifted = get(mals, i).immediate >> 16; // upper 16 bits of the immediate
			inst = newInstruction(lui, 0, 0, 1, shifted, 0, 0, "", "");
			addLast(tals, inst);

			shifted = get(mals, i).immediate << 16;		// lower 16 bits of the immediate
			shifted = shifted >> 16;
			inst = newInstruction(ori, 0, 1, 1, shifted, 0, 0, "", "");
			addLast(tals, inst);

			inst = newInstruction(or, get(mals, i).rt, get(mals, i).rs, 1, 0, 0, 0, "", "");
		}

		// instruction is blt
		else if (id == 10) {
			struct Instruction inst = newInstruction(slt, 1, get(mals, i).rs, get(mals, i).rt, 0, 0, 0, "", "");
			addLast(tals, inst);

			inst = newInstruction(bne, 0, 1, 0, 0, 0, 0, "", get(mals, i).branch_label);
			addLast(tals, inst);
		}

		// instruction is bge
		else if (id == 11) {
			struct Instruction inst = newInstruction(slt, 1, get(mals, i).rs, get(mals, i).rt, 0, 0, 0, "", "");
				addLast(tals, inst);

				inst = newInstruction(beq, 0, 1, 0, 0, 0, 0, "", get(mals, i).branch_label);
				addLast(tals, inst);
		}

		// instruction is mov
		else if (id == 12) {
			struct Instruction inst = newInstruction(addu, get(mals, i).rt, 0, get(mals, i).rs, 0, 0, 0, "", "");
			addLast(tals, inst);
		}

		// if instruction is already TAL, add it to tals
		else { addLast(tals, get(mals,i); }	
	}
}
