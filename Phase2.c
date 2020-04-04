#include "Phase2.h"
#include <stdlib.h>
#include <string.h>

void resolve_addresses(struct ArrayList* unresolved, uint32_t first_pc, struct ArrayList* resolved) {
	struct ArrayList labels = newArrayList();
	int pc = first_pc;

	// gathering all the labels
	for (int i = 0; i < unresolved->size; i++) {
		if (strcmp(get(unresolved, i).label, "") != 0) {
			addLast(labels, newInstruction(0, 0, 0, 0, 0, pc, 0, get(unresolved, i).label, ""));
		}
		pc += 4;
	}

	// determining immediates for branches
	pc = first_pc;
	for (int i = 0; i < unresolved->size; i++) {
		enum ID id = get(unresolved, i).instruction_id;
		if (id == 4 || id == 5 || id == 10 || id == 11) {
			int match = 0; // find the index in labels that has the label we need
			int imm = 0;

			for (int j = 0; j < labels->size; j++) {
				if (strcmp(get(unresolved, i).label, get(labels, j).label) == 0) {
					match = j;
				}
			}

			imm = (get(labels, match).jump_address - (pc + 4)) / 4;
			struct Instruction inst = newInstruction(get(unresolved, i).instruction_id, get(unresolved, i).rd, get(unresolved, i).rs, get(unresolved, i).rt, imm, 0, 0, "", "");
			addLast(resolved, inst);
		}
		
		else { addLast(resolved, get(unresolved, i)); }
		
		pc += 4;
	}
	freeList(labels);
}
