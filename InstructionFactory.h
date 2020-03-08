#pragma once
#include "Instruction.h"


struct Instruction CreateSll(uint8_t rd, uint8_t rt, uint8_t shift_amount);
struct Instruction CreateAddu(uint8_t rd, uint8_t rs, uint8_t rt);
struct Instruction CreateOr(uint8_t rd, uint8_t rs, uint8_t rt);
struct Instruction CreateSlt(uint8_t rd, uint8_t rs, uint8_t rt);
struct Instruction CreateBeq_imm(uint8_t rs, uint8_t rt, int32_t immediate);
struct Instruction CreateBeq(uint8_t rs, uint8_t rt, char *branch_label);
struct Instruction CreateBne_imm(uint8_t rs, uint8_t rt, int32_t immediate);
struct Instruction CreateBne(uint8_t rs, uint8_t rt, char *branch_label);
struct Instruction CreateAddiu(uint8_t rt, uint8_t rs, int32_t immediate);
struct Instruction CreateOri(uint8_t rt, uint8_t rs, int32_t immediate);
struct Instruction CreateLui(uint8_t rt, int32_t immediate);
struct Instruction CreateSll_lab(uint8_t rd, uint8_t rt, uint8_t shift_amount, char *label);
struct Instruction CreateAddu_lab(uint8_t rd, uint8_t rs, uint8_t rt, char *label);
struct Instruction CreateOr_lab(uint8_t rd, uint8_t rs, uint8_t rt, char *label);
struct Instruction CreateSlt_lab(uint8_t rd, uint8_t rs, uint8_t rt, char *label);
struct Instruction CreateBeq_imm_lab(uint8_t rs, uint8_t rt, int32_t immediate, char *label);
struct Instruction CreateBeq_lab(uint8_t rs, uint8_t rt, char *branch_label, char *label);
struct Instruction CreateBne_imm_lab(uint8_t rs, uint8_t rt, int32_t immediate, char *label);
struct Instruction CreateBne_lab(uint8_t rs, uint8_t rt, char *branch_label, char *label);
struct Instruction CreateAddiu_lab(uint8_t rt, uint8_t rs, int32_t immediate, char *label);
struct Instruction CreateOri_lab(uint8_t rt, uint8_t rs, int32_t immediate, char *label);
struct Instruction CreateLui_lab(uint8_t rt, int32_t immediate, char *label);
struct Instruction CreateBlt(uint8_t rt, uint8_t rs, char *branch_label);
struct Instruction CreateBlt_lab(uint8_t rt, uint8_t rs, char *label, char *branch_label);
struct Instruction CreateBge(uint8_t rt, uint8_t rs, char *branch_label);
struct Instruction CreateBge_lab(uint8_t rt, uint8_t rs, char *label, char *branch_label);
struct Instruction CreateMove(uint8_t rd, uint8_t rt);
struct Instruction CreateMove_lab(uint8_t rd, uint8_t rt, char *label);
