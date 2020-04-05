#include "Phase3.h"

uint32_t binary_to_int(char c[]) {
	uint32_t x = 0;
	for (int i = 31; i > -1; i--) {
		if (c[31-i] == '1') { 
			x += (1 << i); 
		}
	}
	return x;
}


// used for 5-bit register numbers
char* int_to_binary5(int x) {
	char c[5];
	for (int i = 4; i > -1; i--) {
		if (x - (1 << i) >= 0) {
			c[4 - i] = '1';
			x -= (1 << i);
		}
		if (x == 0) { break; }
	}
	char* str = c;
	return str;
}

// used for 16-bit immediates
char* int_to_binary16(int x) {
	char c[16];
	for (int i = 15; i > -1; i--) {
		if (x - (1 << i) >= 0) {
			c[15 - i] = '1';
			x -= (1 << i);
		}
		if (x == 0) { break; }
	}
	char* str = c;
	return str;
}

void translate_instructions(struct ArrayList *tals, uint32_t machineCode[]) {
	for (int i = 0; i < tals->size; i++) {
		struct Instruction inst = get(tals, i);
		enum ID id = inst.instruction_id;
		char binary[32];

		// sll
		if (id == 0) {
			for (int i = 0; i < 6; i++) {
				binary[i] = '0';
			}

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary5(inst.rd);
			for (int i = 16; i < 21; i++) {
				binary[i] = c[i - 16];
			}

			c = int_to_binary5(inst.shift_amount);
			for (int i = 21; i < 26; i++) {
				binary[i] = c[i - 21];
			}

			for (int i = 26; i < 32; i++) {
				binary[i] = '0';
			}
		}

		// addu
		else if (id == 1) {
			for (int i = 0; i < 6; i++) {
				binary[i] = '0';
			}

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary5(inst.rd);
			for (int i = 16; i < 21; i++) {
				binary[i] = c[i - 16];
			}

			for (int i = 21; i < 26; i++) {
				binary[i] = '0';
			}

			binary[26] = '1';
			binary[27] = '0';
			binary[28] = '0';
			binary[29] = '0';
			binary[30] = '0';
			binary[31] = '1';
		}

		// or 
		else if (id == 2) {
			for (int i = 0; i < 6; i++) {
				binary[i] = '0';
			}

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary5(inst.rd);
			for (int i = 16; i < 21; i++) {
				binary[i] = c[i - 16];
			}

			for (int i = 21; i < 26; i++) {
				binary[i] = '0';
			}

			binary[26] = '1';
			binary[27] = '0';
			binary[28] = '0';
			binary[29] = '1';
			binary[30] = '0';
			binary[31] = '1';
		}

		// slt
		else if (id == 3) {
			for (int i = 0; i < 6; i++) {
				binary[i] = '0';
			}

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary5(inst.rd);
			for (int i = 16; i < 21; i++) {
				binary[i] = c[i - 16];
			}

			for (int i = 21; i < 26; i++) {
				binary[i] = '0';
			}

			binary[26] = '1';
			binary[27] = '0';
			binary[28] = '1';
			binary[29] = '0';
			binary[30] = '1';
			binary[31] = '0';
		}

		// beq
		else if (id == 4) {
			binary[0] = '0';
			binary[1] = '0';
			binary[2] = '0';
			binary[3] = '1';
			binary[4] = '0';
			binary[5] = '0';

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary16(inst.immediate);
			for (int i = 16; i < 32; i++) {
				binary[i] = c[i - 16];
			}
		}

		// bne
		else if (id == 5) {
			binary[0] = '0';
			binary[1] = '0';
			binary[2] = '0';
			binary[3] = '1';
			binary[4] = '0';
			binary[5] = '1';
		
			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary16(inst.immediate);
			for (int i = 16; i < 32; i++) {
				binary[i] = c[i - 16];
			}
		}

		// addi
		else if (id == 6) {
			binary[0] = '0';
			binary[1] = '0';
			binary[2] = '1';
			binary[3] = '0';
			binary[4] = '0';
			binary[5] = '0';

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary16(inst.immediate);
			for (int i = 16; i < 32; i++) {
				binary[i] = c[i - 16];
			}
		}

		// addiu
		else if (id == 7) {
			binary[0] = '0';
			binary[1] = '0';
			binary[2] = '1';
			binary[3] = '0';
			binary[4] = '0';
			binary[5] = '1';

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary16(inst.immediate);
			for (int i = 16; i < 32; i++) {
				binary[i] = c[i - 16];
			}
		}

		// ori
		else if (id == 8) {
			binary[0] = '0';
			binary[1] = '0';
			binary[2] = '1';
			binary[3] = '1';
			binary[4] = '0';
			binary[5] = '1';

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary16(inst.immediate);
			for (int i = 16; i < 32; i++) {
				binary[i] = c[i - 16];
			}
		}

		// lui
		else {
			binary[0] = '0';
			binary[1] = '0';
			binary[2] = '1';
			binary[3] = '1';
			binary[4] = '1';
			binary[5] = '1';

			char* c = int_to_binary5(inst.rs);
			for (int i = 6; i < 11; i++) {
				binary[i] = c[i - 6];
			}

			c = int_to_binary5(inst.rt);
			for (int i = 11; i < 16; i++) {
				binary[i] = c[i - 11];
			}

			c = int_to_binary16(inst.immediate);
			for (int i = 16; i < 32; i++) {
				binary[i] = c[i - 16];
			}
		}
		
		machineCode[i] = binary_to_int(binary);
	}
}
