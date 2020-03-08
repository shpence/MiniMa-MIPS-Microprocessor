#include "InstructionFactory.h"

struct Instruction CreateSll(uint8_t rd, uint8_t rt, uint8_t shift_amount){
  return CreateSll_lab(rd, rt, shift_amount, "");
}
    /**
    public static Instruction CreateSrl(uint8_t rd, uint8_t rt, uint8_t shift_amount){
        return new Instruction(srl, rd, 0, rt, shift_amount);
    }
    
    public static Instruction CreateSra(uint8_t rd, uint8_t rt, uint8_t shift_amount){
        return new Instruction(sra, rd, 0, rt, shift_amount);
    }
    
    public static Instruction CreateSllv(uint8_t rd, uint8_t rt, uint8_t shift_amount){
        return new Instruction(sllv, rd, 0, rt, shift_amount);
    }
    
    public static Instruction CreateSrlv(uint8_t rd, uint8_t rt, uint8_t shift_amount){
        return new Instruction(srlv, rd, 0, rt, shift_amount);
    }
    
    public static Instruction CreateSrav(uint8_t rd, uint8_t rt, uint8_t shift_amount){
        return new Instruction(srav, rd, 0, rt, shift_amount);
    }
    
    public static Instruction CreateJr(uint8_t rs){
        return new Instruction(jr, 0, rs, 0, 0);
    }
    
    public static Instruction CreateJalr(uint8_t rd, uint8_t rs){
        return new Instruction(jalr, rd, rs, 0, 0);
    }
    
    public static Instruction CreateJalr(uint8_t rs){
        return new Instruction(jalr, 31, rs, 0, 0);
    }
    
    public static Instruction CreateMfhi(uint8_t rd){
        return new Instruction(mfhi, rd, 0, 0, 0);
    }
    
    public static Instruction CreateMthi(uint8_t rs){
        return new Instruction(mthi, 0, rs, 0, 0);
    }
    
    public static Instruction CreateMflo(uint8_t rd){
        return new Instruction(mflo, rd, 0, 0, 0);
    }
    
    public static Instruction CreateMtlo(uint8_t rs){
        return new Instruction(mtlo, 0, rs, 0, 0);
    }
    
    public static Instruction CreateMult(uint8_t rs, uint8_t rt){
        return new Instruction(mult, 0, rs, rt, 0);
    }
    
    public static Instruction CreateMultu(uint8_t rs, uint8_t rt){
        return new Instruction(multu, 0, rs, rt, 0);
    }
    
    public static Instruction CreateDiv(uint8_t rs, uint8_t rt){
        return new Instruction(div, 0, rs, rt, 0);
    }
    
    public static Instruction CreateDivu(uint8_t rs, uint8_t rt){
        return new Instruction(divu, 0, rs, rt, 0);
    }
    
    public static Instruction CreateAdd(uint8_t rd, uint8_t rs, uint8_t rt){
        return new Instruction(add, rd, rs, rt, 0);
    }
    */
    
struct Instruction CreateAddu(uint8_t rd, uint8_t rs, uint8_t rt){
  return CreateAddu_lab(rd, rs, rt, "");
}
    
    /**
    public static Instruction CreateSub(uint8_t rd, uint8_t rs, uint8_t rt){
        return new Instruction(sub, rd, rs, rt, 0);
    }
    
    public static Instruction CreateSubu(uint8_t rd, uint8_t rs, uint8_t rt){
        return new Instruction(subu, rd, rs, rt, 0);
    }
    
    public static Instruction CreateAnd(uint8_t rd, uint8_t rs, uint8_t rt){
        return new Instruction(and, rd, rs, rt, 0);
    }
    */
    
struct Instruction CreateOr(uint8_t rd, uint8_t rs, uint8_t rt){
  return CreateOr_lab(rd, rs, rt, "");
}
    
    /**
    public static Instruction CreateXor(uint8_t rd, uint8_t rs, uint8_t rt){
        return new Instruction(xor, rd, rs, rt, 0);
    }
    
    public static Instruction CreateNor(uint8_t rd, uint8_t rs, uint8_t rt){
        return new Instruction(nor, rd, rs, rt, 0);
    }
    */
    
struct Instruction CreateSlt(uint8_t rd, uint8_t rs, uint8_t rt){
  return CreateSlt_lab(rd, rs, rt, "");
}
    
    /**
    public static Instruction CreateSltu(uint8_t rd, uint8_t rs, uint8_t rt){
        return new Instruction(sltu, rd, rs, rt, 0);
    }
    
    public static Instruction CreateJ(int jump_address){
        return new Instruction(j, jump_address);
    }
    
    public static Instruction CreateJ(char *branch_label){
        return new Instruction(j, branch_label);
    }
    
    public static Instruction CreateJal(int jump_address){
        return new Instruction(jal, jump_address);
    }
    
    public static Instruction CreateJal(char *branch_label){
        return new Instruction(jal, branch_label);
    }
    */
    
    struct Instruction CreateBeq_imm(uint8_t rs, uint8_t rt, int32_t immediate){
        return CreateBeq_imm_lab(rs, rt, immediate, "");
    }
    
    struct Instruction CreateBeq(uint8_t rs, uint8_t rt, char *branch_label){
        return CreateBeq_lab(rs, rt, branch_label, "");
    }
    
    struct Instruction CreateBne_imm(uint8_t rs, uint8_t rt, int32_t immediate){
        return CreateBne_imm_lab(rs, rt, immediate, "");
    }
    
    struct Instruction CreateBne(uint8_t rs, uint8_t rt, char *branch_label){
        return CreateBne_lab(rs, rt, branch_label, "");
    }
    
    /**
    public static Instruction CreateBlez(uint8_t rs, int32_t immediate){
        return new Instruction(blez, rs, 0, immediate);
    }
    
    public static Instruction CreateBlez(uint8_t rs, char *branch_label){
        return new Instruction(blez, rs, 0, branch_label);
    }
    
    public static Instruction CreateBgtz(uint8_t rs, int32_t immediate){
        return new Instruction(bgtz, rs, 0, immediate);
    }
    
    public static Instruction CreateBgtz(uint8_t rs, char *branch_label){
        return new Instruction(bgtz, rs, 0, branch_label);
    }
    
    public static Instruction CreateAddi(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(addi, rs, rt, immediate);
    }
    */
    
    struct Instruction CreateAddiu(uint8_t rt, uint8_t rs, int32_t immediate){
        return CreateAddiu_lab(rt, rs, immediate, "");
    }
    
    /**
    public static Instruction CreateSlti(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(slti, rs, rt, immediate);
    }
    
    public static Instruction CreateSltiu(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(sltiu, rs, rt, immediate);
    }
    
    public static Instruction CreateAndi(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(andi, rs, rt, immediate);
    }
    */
    
    struct Instruction CreateOri(uint8_t rt, uint8_t rs, int32_t immediate){
        return CreateOri_lab(rt, rs, immediate, "");
    }
    
    /**
    public static Instruction CreateXori(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(xori, rs, rt, immediate);
    }
    */
    
    struct Instruction CreateLui(uint8_t rt, int32_t immediate){
        return CreateLui_lab(rt, immediate, "");
    }
    
    /**
    public static Instruction CreateLb(uint8_t rs, int32_t immediate){
        return new Instruction(lb, rs, 0, immediate);
    }
    
    public static Instruction CreateLh(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(lh, rs, rt, immediate);
    }
    
    public static Instruction CreateLw(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(lw, rs, rt, immediate);
    }
    
    public static Instruction CreateLbu(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(lbu, rs, rt, immediate);
    }
    
    public static Instruction CreateLhu(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(lhu, rs, rt, immediate);
    }
    
    public static Instruction CreateSb(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(sb, rs, rt, immediate);
    }
    
    public static Instruction CreateSh(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(sh, rs, rt, immediate);
    }
    
    public static Instruction CreateSw(uint8_t rt, uint8_t rs, int32_t immediate){
        return new Instruction(sw, rs, rt, immediate);
    }
     */
    
struct Instruction CreateSll_lab(uint8_t rd, uint8_t rt, uint8_t shift_amount, char *label){
  return newInstruction(sll, rd, 0, rt, 0, 0, shift_amount, label, "");
}

    /*
    public static Instruction CreateSrl(uint8_t rd, uint8_t rt, uint8_t shift_amount, char *label){
        return new Instruction(srl, rd, 0, rt, shift_amount, label);
    }
    
    public static Instruction CreateSra(uint8_t rd, uint8_t rt, uint8_t shift_amount, char *label){
        return new Instruction(sra, rd, 0, rt, shift_amount, label);
    }
    
    public static Instruction CreateSllv(uint8_t rd, uint8_t rt, uint8_t shift_amount, char *label){
        return new Instruction(sllv, rd, 0, rt, shift_amount, label);
    }
    
    public static Instruction CreateSrlv(uint8_t rd, uint8_t rt, uint8_t shift_amount, char *label){
        return new Instruction(srlv, rd, 0, rt, shift_amount, label);
    }
    
    public static Instruction CreateSrav(uint8_t rd, uint8_t rt, uint8_t shift_amount, char *label){
        return new Instruction(srav, rd, 0, rt, shift_amount, label);
    }
    
    public static Instruction CreateJr(uint8_t rs, char *label){
        return new Instruction(jr, 0, rs, 0, 0, label);
    }
    
    public static Instruction CreateJalr(uint8_t rd, uint8_t rs, char *label){
        return new Instruction(jalr, rd, rs, 0, 0, label);
    }
    
    public static Instruction CreateJalr(uint8_t rs, char *label){
        return new Instruction(jalr, 31, rs, 0, 0, label);
    }
    
    public static Instruction CreateMfhi(uint8_t rd, char *label){
        return new Instruction(mfhi, rd, 0, 0, 0, label);
    }
    
    public static Instruction CreateMthi(uint8_t rs, char *label){
        return new Instruction(mthi, 0, rs, 0, 0, label);
    }
    
    public static Instruction CreateMflo(uint8_t rd, char *label){
        return new Instruction(mflo, rd, 0, 0, 0, label);
    }
    
    public static Instruction CreateMtlo(uint8_t rs, char *label){
        return new Instruction(mtlo, 0, rs, 0, 0, label);
    }
    
    public static Instruction CreateMult(uint8_t rs, uint8_t rt, char *label){
        return new Instruction(mult, 0, rs, rt, 0, label);
    }
    
    public static Instruction CreateMultu(uint8_t rs, uint8_t rt, char *label){
        return new Instruction(multu, 0, rs, rt, 0, label);
    }
    
    public static Instruction CreateDiv(uint8_t rs, uint8_t rt, char *label){
        return new Instruction(div, 0, rs, rt, 0, label);
    }
    
    public static Instruction CreateDivu(uint8_t rs, uint8_t rt, char *label){
        return new Instruction(divu, 0, rs, rt, 0, label);
    }
    
    public static Instruction CreateAdd(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return new Instruction(add, rd, rs, rt, 0, label);
    }
    */
    
    struct Instruction CreateAddu_lab(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return newInstruction(addu, rd, rs, rt, 0, 0, 0, label, "");
    }
    
    /**
    public static Instruction CreateSub(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return new Instruction(sub, rd, rs, rt, 0, label);
    }
    
    public static Instruction CreateSubu(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return new Instruction(subu, rd, rs, rt, 0, label);
    }
    
    public static Instruction CreateAnd(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return new Instruction(and, rd, rs, rt, 0, label);
    }
    */
    
    struct Instruction CreateOr_lab(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return newInstruction(or, rd, rs, rt, 0, 0, 0, label, "");
    }
    
    /**
    public static Instruction CreateXor(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return new Instruction(xor, rd, rs, rt, 0, label);
    }
    
    public static Instruction CreateNor(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return new Instruction(nor, rd, rs, rt, 0, label);
    }
    */
    
    struct Instruction CreateSlt_lab(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return newInstruction(slt, rd, rs, rt, 0, 0, 0, label, "");
    }
    
    /**
    public static Instruction CreateSltu(uint8_t rd, uint8_t rs, uint8_t rt, char *label){
        return new Instruction(sltu, rd, rs, rt, 0, label);
    }
    
    public static Instruction CreateJ(int jump_address, char *label){
        return new Instruction(j, jump_address, label);
    }
    
    public static Instruction CreateJ(char *branch_label, char *label){
        return new Instruction(j, branch_label, label);
    }
    
    public static Instruction CreateJal(int jump_address, char *label){
        return new Instruction(jal, jump_address, label);
    }
    
    public static Instruction CreateJal(char *branch_label, char *label){
        return new Instruction(jal, branch_label, label);
    }
    */
    
    struct Instruction CreateBeq_imm_lab(uint8_t rs, uint8_t rt, int32_t immediate, char *label){
        return newInstruction(beq, 0, rs, rt, immediate, 0, 0, label, "");
    }
    
    struct Instruction CreateBeq_lab(uint8_t rs, uint8_t rt, char *branch_label, char *label){
        return newInstruction(beq, 0, rs, rt, 0, 0, 0, label, branch_label);
    }
    
    struct Instruction CreateBne_imm_lab(uint8_t rs, uint8_t rt, int32_t immediate, char *label){
        return newInstruction(bne, 0, rs, rt, immediate, 0, 0, label, "");
    }
    
    struct Instruction CreateBne_lab(uint8_t rs, uint8_t rt, char *branch_label, char *label){
        return newInstruction(bne, 0, rs, rt, 0, 0, 0, label, branch_label);
    }
    
    /**
    public static Instruction CreateBlez(uint8_t rs, int32_t immediate, char *label){
        return new Instruction(blez, rs, 0, immediate, label);
    }
    
    public static Instruction CreateBlez(uint8_t rs, char *branch_label, char *label){
        return new Instruction(blez, rs, 0, branch_label, label);
    }
    
    public static Instruction CreateBgtz(uint8_t rs, int32_t immediate, char *label){
        return new Instruction(bgtz, rs, 0, immediate, label);
    }
    
    public static Instruction CreateBgtz(uint8_t rs, char *branch_label, char *label){
        return new Instruction(bgtz, rs, 0, branch_label, label);
    }
    
    public static Instruction CreateAddi(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(addi, rs, rt, immediate, label);
    }
    */
    
    struct Instruction CreateAddiu_lab(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return newInstruction(addiu, 0, rs, rt, immediate, 0, 0, label, "");
    }
    
    /**
    public static Instruction CreateSlti(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(slti, rs, rt, immediate, label);
    }
    
    public static Instruction CreateSltiu(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(sltiu, rs, rt, immediate, label);
    }
    
    public static Instruction CreateAndi(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(andi, rs, rt, immediate, label);
    }
    */
    
    struct Instruction CreateOri_lab(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return newInstruction(ori, 0, rs, rt, immediate, 0, 0, label, "");
    }
    
    /**
    public static Instruction CreateXori(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(xori, rs, rt, immediate, label);
    }
    */
    
    struct Instruction CreateLui_lab(uint8_t rt, int32_t immediate, char *label){
        return newInstruction(lui, 0, 0, rt, immediate, 0, 0, label, "");
    }
    
    /**
    public static Instruction CreateLb(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(lb, rs, rt, immediate, label);
    }
    
    public static Instruction CreateLh(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(lh, rs, rt, immediate, label);
    }
    
    public static Instruction CreateLw(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(lw, rs, rt, immediate, label);
    }
    
    public static Instruction CreateLbu(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(lbu, rs, rt, immediate, label);
    }
    
    public static Instruction CreateLhu(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(lhu, rs, rt, immediate, label);
    }
    
    public static Instruction CreateSb(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(sb, rs, rt, immediate, label);
    }
    
    public static Instruction CreateSh(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(sh, rs, rt, immediate, label);
    }
    
    public static Instruction CreateSw(uint8_t rt, uint8_t rs, int32_t immediate, char *label){
        return new Instruction(sw, rs, rt, immediate, label);
    }
    */
    
    //pseudo instructions
    struct Instruction CreateBlt(uint8_t rt, uint8_t rs, char *branch_label){
        return CreateBlt_lab(rt, rs, "", branch_label);
    }
    
    struct Instruction CreateBlt_lab(uint8_t rt, uint8_t rs, char *label, char *branch_label){
        return newInstruction(blt, 0, rs, rt, 0, 0, 0, label, branch_label);
    }
    
    struct Instruction CreateBge(uint8_t rt, uint8_t rs, char *branch_label){
        return CreateBge_lab(rt, rs, "", branch_label);
    }
    
    struct Instruction CreateBge_lab(uint8_t rt, uint8_t rs, char *label, char *branch_label){
        return newInstruction(bge, 0, rs, rt, 0, 0, 0, label, branch_label);
    }

    struct Instruction CreateMove(uint8_t rd, uint8_t rt){
        return CreateMove_lab(rd, rt, "");
    }

    struct Instruction CreateMove_lab(uint8_t rd, uint8_t rt, char *label){
        return newInstruction(mov, rd, 0, rt, 0, 0, 0, label, "");
    }
