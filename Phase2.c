#include "Phase2.h"

// Label struct to handle nontransmutable nature of the ArrayList struct
struct Label {
	char label_name[MAX_LABEL_LENGTH];
	int address;
};

void resolve_addresses(struct ArrayList *unresolved, uint32_t first_pc, struct ArrayList *resolved) {
	struct Label* labels[];
	int labels_size = 0;
	int pc = first_pc;
	for (int i = 0; i < unresolved->size; i++) {
		if (get(unresolved, i).label != "") {
			struct Label *add = malloc(sizeof(struct Label));
			add->label_name = get(unresolved, i).label;
			add->address = pc;
			labels[labels_size] = add;
			labels_size += 1;
		}
		pc += 4;
	}

	pc = first_pc;
	for (int i = 0; i < unresolved->size; i++) {
		enum ID id = get(unresolved, i).instruction_id;
		if (id == 4 || id == 5 || id == 10 || id == 11) {
			struct Label* l;
			int imm = 0;

			for (int j = 0; j < labels_size; j++) {
				if (strcmp(get(unresolved, i).label, labels[j]->label_name) == 0) {
					l = labels[j];
				}
			}

			imm = (l->address - (pc + 4)) / 4;
			struct Instruction inst = newInstruction(get(unresolved, i).instruction_id, get(unresolved, i).rd, get(unresolved, i).rs, get(unresolved, i).rt, imm, 0, 0, "", "");
			addLast(resolved, inst);
		}
		
		else { addLast(resolved, get(unresolved, i)); }
		
		pc += 4;
	}
}
