#include "AssemblerException.h"
#include "Instruction.h"
#include <stdio.h>
#include <string.h>

    
struct Instruction newInstructionBlank() {
  return newInstruction(addiu, 0, 0, 0, 0, 0, 0, "", "");
}

struct Instruction newInstruction(enum ID instruction_id, uint8_t rd, uint8_t rs, uint8_t rt, int32_t immediate, uint32_t jump_address, uint8_t shift_amount, char *label, char *branch_label) {
  if (rd >= 32 || rd < 0) assemblerException("Unrecognized register: %d", rd);
  if (rs >= 32 || rs < 0) assemblerException("Unrecognized register: %d", rs);
  if (rt >= 32 || rt < 0) assemblerException("Unrecognized register: %d", rt);
  if (shift_amount >= 32 || shift_amount < 0) assemblerException("shift amount out of range: %d", shift_amount);

  struct Instruction r;
  r.instruction_id = instruction_id;
  r.rd = rd;
  r.rs = rs;
  r.rt = rt;
  r.immediate = immediate;
  r.jump_address = jump_address;
  r.shift_amount = shift_amount;
  strncpy(r.label, label, MAX_LABEL_LENGTH);
  strncpy(r.branch_label, branch_label, MAX_LABEL_LENGTH);

  return r;
}

bool equal(struct Instruction a, struct Instruction b) {
  return a.instruction_id == b.instruction_id
      && a.rd == b.rd
      && a.rs == b.rs
      && a.rt == b.rt
      && a.immediate == b.immediate
      && a.jump_address == b.jump_address
      && a.shift_amount == b.shift_amount
      && strncmp(a.label, b.label, MAX_LABEL_LENGTH) == 0
      && strncmp(a.label, b.label, MAX_LABEL_LENGTH) == 0;
}
    
/*
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Instruction that = (Instruction) o;

        if (instruction_id != that.instruction_id) return false;
        if (rd != that.rd) return false;
        if (rs != that.rs) return false;
        if (rt != that.rt) return false;
        if (immediate != that.immediate) return false;
        if (jump_address != that.jump_address) return false;
        if (shift_amount != that.shift_amount) return false;
        if (label == null ? that.label != null : !label.equals(that.label)) return false;
        return (branch_label == null ? that.branch_label == null : branch_label.equals(that.branch_label));

    }

    @Override
    public int hashCode() {
        int result = instruction_id.hashCode();
        result = 31 * result + rd;
        result = 31 * result + rs;
        result = 31 * result + rt;
        result = 31 * result + immediate;
        result = 31 * result + jump_address;
        result = 31 * result + shift_amount;
        result = 31 * result + label.hashCode();
        result = 31 * result + branch_label.hashCode();
        return result;
    }
*/

void toString(struct Instruction this, char *result) {
  sprintf(result, "Instruction{instruction_id=%u"
      ", rd=%u"
      ", rs=%u"
      ", rt=%u"
      ", immediate=%d"
      ", jump_address=%u"
      ", shift_amount=%u"
      ", label_id=%s"
      ", branch_label=%s"
      "}", 
      this.instruction_id,
      this.rd,
      this.rs,
      this.rt,
      this.immediate,
      this.jump_address,
      this.shift_amount,
      this.label,
      this.branch_label);
}
