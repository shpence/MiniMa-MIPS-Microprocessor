#include <assert.h>
#include <stdlib.h>
#include "Instruction.h"
#include "InstructionFactory.h"
#include "ArrayList.h"
#include "Phase1.h"
#include "Phase2.h"
#include "Phase3.h"

const int MARS_TEXT_SEGMENT_START = 0x00400000;

void testHelperPhase1(struct ArrayList *input, struct ArrayList *expectedP1) {
  // Phase 1
  struct ArrayList *tals = newArrayList();

  mal_to_tal(input, tals);
  // same length?
  assert(size(expectedP1) == size(tals));
  // same objects?
  for(int i = 0; i < size(expectedP1); i++){
    assert(equal(get(expectedP1, i), get(tals, i)));
  }

  freeList(tals);
}
        
void testHelperPhase2(struct ArrayList *expectedP1, struct ArrayList *expectedP2) {
  // assertion not a test
  assert(size(expectedP1) == size(expectedP2));

  // Phase 2
  struct ArrayList *resolved_tals = newArrayList();

  resolve_addresses(expectedP1, MARS_TEXT_SEGMENT_START, resolved_tals);
  // same length?
  assert(size(expectedP2) == size(resolved_tals));
  // same objects?
  for(int i = 0; i < size(expectedP2); i++){
    assert(equal(get(expectedP2, i), get(resolved_tals, i)));
  }

  freeList(resolved_tals);
}
        
void testHelperPhase3(struct ArrayList *expectedP2, uint32_t expectedP3[]) {
  // Phase 3
  uint32_t *translated = malloc(size(expectedP2) * sizeof(uint32_t)); 

  translate_instructions(expectedP2, translated);
  // same objects?
  for(int i = 0; i < size(expectedP2); i++){
    assert(expectedP3[i] == translated[i]);
  }
  
  free(translated);
}

void test1Phase1() {
  struct Instruction input[4] = {
    // label1: addu $t0, $zero, $zero
    CreateAddu_lab(8, 0, 0, "label1"),
    // addu $s0, $s7, $t4
    CreateAddu(16, 23, 12),
    // blt  $s0,$t0,label1
    CreateBlt(16, 8, "label1"),
    // addiu $s1,$s2,0xF00000
    CreateAddiu(17, 18, 0xF00000),
  };
  // Phase 1
  struct Instruction phase1_expected[7] = {
    CreateAddu_lab(8, 0, 0, "label1"), // label1: addu $t0, $zero, $zero
    CreateAddu(16, 23, 12), // addu $s0, $s7, $t4
    CreateSlt(1, 16, 8),  // slt $at,$s0,$t0
    CreateBne(1, 0, "label1"),     // bne $at,$zero,label1
    CreateLui(1, 0xF0), // lui $at, 0x00F0
    CreateOri(1, 1, 0), // ori $at, $at 0x0000
    CreateAddu(17, 18, 1) // addu $s1,$s2,$at
  };
  struct ArrayList *inputL = fromArray(input, 4);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 7);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test1Phase2() {
  // Phase 1
  struct Instruction phase1_expected[7] = {
    CreateAddu_lab(8, 0, 0, "label1"), // label1: addu $t0, $zero, $zero
    CreateAddu(16, 23, 12), // addu $s0, $s7, $t4
    CreateSlt(1, 16, 8),  // slt $at,$s0,$t0
    CreateBne(1, 0, "label1"),     // bne $at,$zero,label1
    CreateLui(1, 0xF0), // lui $at, 0x00F0
    CreateOri(1, 1, 0), // ori $at, $at 0x0000
    CreateAddu(17, 18, 1) // addu $s1,$s2,$at
  };

  // Phase 2
  struct Instruction phase2_expected[7] = {
    CreateAddu_lab(8,0, 0, "label1"),
    CreateAddu(16,23,12),
    CreateSlt(1, 16, 8),
    CreateBne_imm(1, 0, -4),
    CreateLui(1, 0xF0),
    CreateOri(1, 1, 0),
    CreateAddu(17, 18, 1)
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 7);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 7);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test1Phase3() {
  // Phase 2
  struct Instruction phase2_expected[7] = {
    CreateAddu_lab(8,0, 0, "label1"),
    CreateAddu(16,23,12),
    CreateSlt(1, 16, 8),
    CreateBne_imm(1, 0, -4),
    CreateLui(1, 0xF0),
    CreateOri(1, 1, 0),
    CreateAddu(17, 18, 1)
  };

  // Phase 3
  uint32_t phase3_expected[7] = {
    // HINT: to get these, type the input program into MARS, assemble, and copy the binary values into your test case
    0x00004021,
    0x02ec8021,
    0x0208082a,
    0x1420fffc,
    0x3c0100f0,
    0x34210000,
    0x02418821
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 7);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}
        
void test2Phase1() { 
  struct Instruction input[4] = {
    // Label1: addiu $t0, 0, imm: 1 (less than 16 bit imm)
    CreateAddiu_lab(8, 0, 1, "label1"),
    // Label2: addiu $t1, 0, imm: 0 (also less than 16 bit imm)
    CreateAddiu_lab(9, 0, 0, "label2"),
    // bge $t0, $t1, Label1
    CreateBge(9, 8, "label1"),
    // bge $t1, $t0, Label2
    CreateBge(8, 9, "label2")
  };

  //Phase 1:
  struct Instruction phase1_expected[6] = {
    CreateAddiu_lab(8, 0, 1, "label1"),
    CreateAddiu_lab(9, 0, 0, "label2"),
    CreateSlt(1, 9, 8),
    CreateBeq(1, 0, "label1"),
    CreateSlt(1, 8, 9),
    CreateBeq(1, 0, "label2")
  };

  struct ArrayList *inputL = fromArray(input, 4);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 6);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test2Phase2() {
  //Phase 1:
  struct Instruction phase1_expected[6] = {
    CreateAddiu_lab(8, 0, 1, "label1"),
    CreateAddiu_lab(9, 0, 0, "label2"),
    CreateSlt(1, 9, 8),
    CreateBeq(1, 0, "label1"),
    CreateSlt(1, 8, 9),
    CreateBeq(1, 0, "label2")
  };

  //Phase 2:
  struct Instruction phase2_expected[6] = {
    CreateAddiu_lab(8, 0, 1, "label1"),
    CreateAddiu_lab(9, 0, 0, "label2"),
    CreateSlt(1, 9, 8),
    CreateBeq_imm(1, 0, -4),
    CreateSlt(1, 8, 9),
    CreateBeq_imm(1, 0, -5)
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 6);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 6);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test2Phase3() {
  //Phase 2:
  struct Instruction phase2_expected[6] = {
    CreateAddiu_lab(8, 0, 1, "label1"),
    CreateAddiu_lab(9, 0, 0, "label2"),
    CreateSlt(1, 9, 8),
    CreateBeq_imm(1, 0, -4),
    CreateSlt(1, 8, 9),
    CreateBeq_imm(1, 0, -5)
  };

  //Phase 3:   
  uint32_t phase3_expected[6] = {
    0x24080001,
    0x24090000,
    0x0128082a,
    0x1020fffc,
    0x0109082a,
    0x1020fffb
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 6);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}
        
void test3Phase1() {
  struct Instruction input[2] = {
    // label1: addiu $t0, $zero, -5
    CreateAddiu_lab(8, 0, -5, "label1"),
    // bge $t0, $zero, label1
    CreateBge(8, 0, "label1")
  };

  // Phase 1
  struct Instruction phase1_expected[3] = {
    CreateAddiu_lab(8, 0, -5, "label1"), // label1: addiu $t0, $zero, -5
    CreateSlt(1, 8, 0), // slt $at, $t0, $zero 
    CreateBeq(1, 0, "label1") // beq $at, $zero, label1
  };

  struct ArrayList *inputL = fromArray(input, 2);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 3);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test3Phase2() {
  // Phase 1
  struct Instruction phase1_expected[3] = {
    CreateAddiu_lab(8, 0, -5, "label1"), // label1: addiu $t0, $zero, -5
    CreateSlt(1, 8, 0), // slt $at, $t0, $zero 
    CreateBeq(1, 0, "label1") // beq $at, $zero, label1
  };

  // Phase 2
  struct Instruction phase2_expected[3] = {
    CreateAddiu_lab(8, 0, -5, "label1"),
    CreateSlt(1, 8, 0),
    CreateBeq_imm(1, 0, -3)
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 3);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 3);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test3Phase3() {
  // Phase 2
  struct Instruction phase2_expected[3] = {
    CreateAddiu_lab(8, 0, -5, "label1"),
    CreateSlt(1, 8, 0),
    CreateBeq_imm(1, 0, -3)
  };

  // Phase 3
  uint32_t phase3_expected[3] = {
    // HINT: to get these, type the input program into MARS, assemble, and copy the binary values into your test case
    0x2408fffb,
    0x0100082a,
    0x1020fffd
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 3);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}
        
void test4Phase1() {
  struct Instruction input[6] = {
    CreateAddiu(19, 0, 22),
    CreateAddiu(9,0,10),
    CreateBge(19, 9, "label4"),
    CreateOr(20, 19, 9),
    CreateAddu_lab(21,20,19,"label4"),
    CreateOri(11,9,44)
  };
  //Phase1
  struct Instruction phase1_expected[7] ={
    CreateAddiu(19, 0, 22),
    CreateAddiu(9,0,10),
    CreateSlt( 1,19,9 ),
    CreateBeq(1, 0, "label4"),
    CreateOr(20,19,9),
    CreateAddu_lab(21, 20 , 19,"label4"),
    CreateOri(11, 9, 44)
  };
            
  struct ArrayList *inputL = fromArray(input, 6);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 7);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test4Phase2() {
  //Phase1
  struct Instruction phase1_expected[7] ={
    CreateAddiu(19, 0, 22),
    CreateAddiu(9,0,10),
    CreateSlt( 1,19,9 ),
    CreateBeq(1, 0, "label4"),
    CreateOr(20,19,9),
    CreateAddu_lab(21, 20 , 19,"label4"),
    CreateOri(11, 9, 44)
  };

  struct Instruction phase2_expected[7] ={
    CreateAddiu(19, 0, 22),
    CreateAddiu(9,0,10),
    CreateSlt( 1,19,9 ),
    CreateBeq_imm(1, 0, 1),
    CreateOr(20,19,9),
    CreateAddu_lab(21, 20 , 19,"label4"),
    CreateOri(11, 9, 44)
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 7);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 7);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test4Phase3() {
  struct Instruction phase2_expected[7]={
    CreateAddiu(19, 0, 22),
    CreateAddiu(9,0,10),
    CreateSlt( 1,19,9 ),
    CreateBeq_imm(1, 0, 1),
    CreateOr(20,19,9),
    CreateAddu_lab(21, 20 , 19,"label4"),
    CreateOri(11, 9, 44)
  };

  uint32_t phase3_expected[7]={
    0x24130016,
    0x2409000a,
    0x0269082a,
    0x10200001,
    0x0269a025,
    0x0293a821,
    0x352b002c
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 7);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}
        
void test5Phase1() {
  struct Instruction input[3] = {
    // bge $s0, $s1, A
    CreateBge(16, 17, "A"),
    // addiu $t0, $t1, 0xA31
    CreateAddiu(8, 9, 0xA31),
    // A: or $t0, $zero, $t1
    CreateOr_lab(8, 0, 9, "A"),
  };
  // Phase 1
  struct Instruction phase1_expected[4] = {
    CreateSlt(1, 16, 17),  // slt $at,$s0,$s1
    CreateBeq(1, 0, "A"),     // beq $at,$zero,A
    CreateAddiu(8, 9, 0xA31), //addiu $t0, $t1, 0xA31
    CreateOr_lab(8,0,9,"A") //A: or $t0, $zero, $t1
  };

  struct ArrayList *inputL = fromArray(input, 3);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 4);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test5Phase2() {
  // Phase 1
  struct Instruction phase1_expected[4] = {
    CreateSlt(1, 16, 17),  // slt $at,$s0,$s1
    CreateBeq(1, 0, "A"),     // beq $at,$zero,A
    CreateAddiu(8, 9, 0xA31), //addiu $t0, $t1, 0xA31
    CreateOr_lab(8,0,9,"A") //A: or $t0, $zero, $t1
  };

  // Phase 2
  struct Instruction phase2_expected[4] = {
    CreateSlt(1, 16, 17),  // slt $at,$s0,$t0
    CreateBeq_imm(1, 0, 1),     // beq $at,$zero,A
    CreateAddiu(8,9,0xA31), //addiu $t0, $t1, 0xA31
    CreateOr_lab(8,0,9,"A") // A: or $t0, $zer0, $t1
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 4);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 4);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test5Phase3() {
  // Phase 2
  struct Instruction phase2_expected[4] = {
    CreateSlt(1, 16, 17),  // slt $at,$s0,$t0
    CreateBeq_imm(1, 0, 1),     // beq $at,$zero,A
    CreateAddiu(8,9,0xA31), //addiu $t0, $t1, 0xA31
    CreateOr_lab(8,0,9,"A") // A: or $t0, $zer0, $t1
  };

  // Phase 3
  uint32_t phase3_expected[4] = {
    // HINT: to get these, type the input program into MARS, assemble, and copy the binary values into your test case
    0x0211082A,
    0x10200001,
    0x25280A31,
    0x00094025
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 4);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}
        
void test6Phase1() {
  struct Instruction input[5] = {
    // target: addu $t0, $zero, $zero
    CreateAddu_lab(8, 0, 0, "target"),
    CreateAddu(16, 17, 9),
    // blt  $s0,$t0,target
    CreateBlt(16, 8, "target"),
    // addiu $s1,$s2,0xF00000
    CreateAddiu(17, 18, 0xF00000),
    // ori $s1, $s1, 0xF000
    CreateOri(17, 17, 0xF000)
  };
  // Phase 1
  struct Instruction phase1_expected[8] = {
    CreateAddu_lab(8, 0, 0, "target"), // target: addu $t0, $zero, $zero
    CreateAddu(16, 17, 9), // addu $s0, $s1, $t1
    CreateSlt(1, 16, 8),  // slt $at,$s0,$t0
    CreateBne(1, 0, "target"),     // bne $at,$zero,target
    CreateLui(1, 0xF0), // lui $at, 0x00F0
    CreateOri(1, 1, 0), // ori $at, $at 0x0000
    CreateAddu(17, 18, 1), // addu $s1,$s2,$at
    CreateOri(17, 17, 0xF000)
  };

  struct ArrayList *inputL = fromArray(input, 5);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 8);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test6Phase2() {
  // Phase 1
  struct Instruction phase1_expected[8] = {
    CreateAddu_lab(8, 0, 0, "target"), // target: addu $t0, $zero, $zero
    CreateAddu(16, 17, 9), // addu $s0, $s1, $t1
    CreateSlt(1, 16, 8),  // slt $at,$s0,$t0
    CreateBne(1, 0, "target"),     // bne $at,$zero,target
    CreateLui(1, 0xF0), // lui $at, 0x00F0
    CreateOri(1, 1, 0), // ori $at, $at 0x0000
    CreateAddu(17, 18, 1), // addu $s1,$s2,$at
    CreateOri(17, 17, 0xF000)
  };

  // Phase 2
  struct Instruction phase2_expected[8] = {
    CreateAddu_lab(8,0, 0, "target"),
    CreateAddu(16,17,9),
    CreateSlt(1, 16, 8),
    CreateBne_imm(1, 0, -4),
    CreateLui(1, 0xF0),
    CreateOri(1, 1, 0),
    CreateAddu(17, 18, 1),
    CreateOri(17, 17, 0xF000)
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 8);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 8);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test6Phase3() {
  // Phase 2
  struct Instruction phase2_expected[8] = {
    CreateAddu_lab(8,0, 0, "target"),
    CreateAddu(16,17,9),
    CreateSlt(1, 16, 8),
    CreateBne_imm(1, 0, -4),
    CreateLui(1, 0xF0),
    CreateOri(1, 1, 0),
    CreateAddu(17, 18, 1),
    CreateOri(17, 17, 0xF000)
  };

  // Phase 3
  uint32_t phase3_expected[8] = {
    0x00004021,
    0x02298021,
    0x0208082a,
    0x1420fffc,
    0x3c0100f0,
    0x34210000,
    0x02418821,
    0x3631F000
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 8);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}
        
void test7Phase1() {
  struct Instruction input[8] = {
    // or $t1, $t3, $t4
    CreateOr(9, 11, 12),
    // addu $t0, $zero, $t9
    CreateAddu(8, 0, 25),
    // label1: addu $s0, $s7, $t4
    CreateAddu_lab(16, 23, 12, "label1"),
    // bne $t1, $t7, label2
    CreateBne(9, 15, "label2"),
    // addu $t1, $t1, $s0
    CreateAddu(9, 9, 16),
    // bge $s2,$zero,label1
    CreateBge(0, 18, "label1"),
    // addiu $s1,$s2,0xFFFFFF000
    CreateAddiu(17, 18, 0xFFFFF000),
    // label2: addu $t0, $t0, $t1
    CreateAddu_lab(8, 8, 9,"label2")
  };
  // Phase 1
  struct Instruction phase1_expected[9] = {
    CreateOr(9, 11, 12), // or $t1, $t3, $t4
    CreateAddu(8, 0, 25), // addu $t0, $zero, $t9
    CreateAddu_lab(16, 23, 12, "label1"),  // label1: addu $s0, $s7, $t4
    CreateBne(9, 15, "label2"), // bne $t1, $t7, label2
    CreateAddu(9, 9, 16), // addu $t1, $t1, $s0
    CreateSlt(1, 0, 18), // slt $at, $s2, $zero
    CreateBeq(1, 0, "label1"), // beq $at, $zero, "label1"
    CreateAddiu(17, 18, 0xFFFFF000), // addiu $s1,$s2,0xfffff000
    CreateAddu_lab(8, 8, 9, "label2") // label2: addu $t0, $t0, $t1
  };

  struct ArrayList *inputL = fromArray(input, 8);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 9);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test7Phase2() {
  // Phase 1
  struct Instruction phase1_expected[9] = {
    CreateOr(9, 11, 12), // or $t1, $t3, $t4
    CreateAddu(8, 0, 25), // addu $t0, $zero, $t9
    CreateAddu_lab(16, 23, 12, "label1"),  // label1: addu $s0, $s7, $t4
    CreateBne(9, 15, "label2"), // bne $t1, $t7, label2
    CreateAddu(9, 9, 16), // addu $t1, $t1, $s0
    CreateSlt(1, 0, 18), // slt $at, $s2, $zero
    CreateBeq(1, 0, "label1"), // beq $at, $zero, "label1"
    CreateAddiu(17, 18, 0xFFFFF000), // addiu $s1,$s2,0xfffff000
    CreateAddu_lab(8, 8, 9, "label2") // label2: addu $t0, $t0, $t1
  };

  // Phase 2
  struct Instruction phase2_expected[9] = {
    CreateOr(9, 11, 12), // or $t1, $t3, $t4
    CreateAddu(8, 0, 25), // addu $t0, $zero, 10
    CreateAddu_lab(16, 23, 12, "label1"),  // label1: addu $s0, $s7, $t4
    CreateBne_imm(9, 15, 4), // bne $t1, 12, label2
    CreateAddu(9, 9, 16), // addu $t1, $t1, 1
    CreateSlt(1, 0, 18), // slt $at, $t4, $s0
    CreateBeq_imm(1, 0, -5), // beq $a0, $zero, "label1"
    CreateAddiu(17, 18, 0xFFFFF000), // addu $s1,$s2,0xfffff000
    CreateAddu_lab(8, 8, 9, "label2") // label2: addu $t0, $t0, $t1
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 9);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 9);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test7Phase3() {
  // Phase 2
  struct Instruction phase2_expected[9] = {
    CreateOr(9, 11, 12), // or $t1, $t3, $t4
    CreateAddu(8, 0, 25), // addu $t0, $zero, 10
    CreateAddu_lab(16, 23, 12, "label1"),  // label1: addu $s0, $s7, $t4
    CreateBne_imm(9, 15, 4), // bne $t1, 12, label2
    CreateAddu(9, 9, 16), // addu $t1, $t1, 1
    CreateSlt(1, 0, 18), // slt $at, $t4, $s0
    CreateBeq_imm(1, 0, -5), // beq $a0, $zero, "label1"
    CreateAddiu(17, 18, 0xFFFFF000), // addu $s1,$s2,0xfffff000
    CreateAddu_lab(8, 8, 9, "label2") // label2: addu $t0, $t0, $t1
  };

  // Phase 3
  uint32_t phase3_expected[9] = {
    // HINT: to get these, type the input program into MARS, assemble, and copy the binary values into your test case
    0x016c4825,
    0x00194021,
    0x02ec8021,
    0x152f0004,
    0x01304821,
    0x0012082a,
    0x1020fffb,
    0x2651f000,
    0x01094021
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 9);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}

void test8Phase1() {
  struct Instruction input[5] = {
    // label1: addu $t1, $zero, $zero
    CreateAddu(9, 0, 0),
    // addu $s1, $s8, $t5
    CreateAddu(17, 24, 13),
    // bge $s1, $t1, label1
    CreateBge(17, 9, "label1"),
    // addu $s1, $s6, $t3
    CreateAddu(17, 22, 11),
    // ori $t0, 0x0300, 0x12045, label1
    CreateOri_lab(8, 8, 0x12045, "label1"),
  };

  // Phase 1
  struct Instruction phase1_expected[8] = {
    CreateAddu(9, 0, 0), 
    CreateAddu(17, 24, 13), 
    CreateSlt(1, 17, 9),  // slt $at,$s0,$t0
    CreateBeq(1, 0, "label1"),     // bne $at,$zero,label1
    CreateAddu(17, 22, 11),
    CreateLui_lab(1, 0x0001, "label1"),    
    CreateOri(1, 1, 0x2045), 
    CreateOr(8, 8, 1) 
  };

  struct ArrayList *inputL = fromArray(input, 5);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 8);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test8Phase2() {
  // Phase 1
  struct Instruction phase1_expected[8] = {
    CreateAddu(9, 0, 0), 
    CreateAddu(17, 24, 13), 
    CreateSlt(1, 17, 9),  // slt $at,$s0,$t0
    CreateBeq(1, 0, "label1"),     // bne $at,$zero,label1
    CreateAddu(17, 22, 11),
    CreateLui_lab(1, 0x0001, "label1"),    
    CreateOri(1, 1, 0x2045), 
    CreateOr(8, 8, 1) 
  };

  struct Instruction phase2_expected[8] = {
    CreateAddu(9, 0, 0), //addu $t1, $0, $0
    CreateAddu(17, 24, 13), //addu $s1, $t8, $t5
    CreateSlt(1, 17, 9),  // slt $at,$s1,$t1
    CreateBeq_imm(1, 0, 1),     // beq $at,$zero,label1
    CreateAddu(17, 22, 11), //addu $s1, $s6, $t3
    CreateLui_lab(1, 0x0001, "label1"), //lui $at, 0x0001, "label1"
    CreateOri(1, 1, 0x2045), //$at, $at, 0x2045
    CreateOr(8,8, 1) //addu $t0, $t0, $at
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 8);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 8);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test8Phase3() {
  // Phase 2
  struct Instruction phase2_expected[8] = {
    CreateAddu(9, 0, 0), //addu $t1, $0, $0
    CreateAddu(17, 24, 13), //addu $s1, $t8, $t5
    CreateSlt(1, 17, 9),  // slt $at,$s1,$t1
    CreateBeq_imm(1, 0, 1),     // beq $at,$zero,label1
    CreateAddu(17, 22, 11), //addu $s1, $s6, $t3
    CreateLui_lab(1, 0x0001, "label1"), //lui $at, 0x0001, "label1"
    CreateOri(1, 1, 0x2045), //$at, $at, 0x2045
    CreateOr(8,8, 1) //addu $t0, $t0, $at
  };

  // Phase 3
  uint32_t phase3_expected[8] = {
    0x00004821,
    0x030D8821,
    0x0229082A,
    0x10200001, 
    0x02CB8821,
    0x3C010001,
    0x34212045,
    0x01014025  
  }; 

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 8);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}
        
void test9Phase1() {
  struct Instruction input[5] = {
    //label9: addiu $t0, $zero, 0xFFFFFFF
    CreateAddiu_lab(8, 0, 0xFFFFFFF, "label9"),
    //slt $t1, $zero, $t0
    CreateSlt(9, 0, 8),
    //label5: or $t2, $t1, $t0
    CreateOr_lab(10, 9, 8, "label5"),
    //bgt $zero, $t0, label5
    CreateBge(8, 0, "label5"),
    //ori $t3, $t0, 10
    CreateOri(11, 8, 10)
  };
  // Phase 1
  struct Instruction phase1_expected[8] = {
    CreateLui_lab(1, 0x0FFF, "label9"), // label1: lui $t0, 0x0FFF
    CreateOri(1, 1, 0xFFFF), // ori $at, $at, 0xFFFF
    CreateAddu(8, 0, 1),  // addu $t0,$at,$zero
    CreateSlt(9, 0, 8),     // slt $t1,$zero,$t1
    CreateOr_lab(10, 9, 8, "label5"), // label5: or $t2, $t1, $t0
    CreateSlt(1, 8, 0), // slt $at, $zero, $t0
    CreateBeq(1, 0, "label5"), // bne $at,$zero,label5
    CreateOri(11, 8, 10) // ori $t3,$t0,10 
  };

  struct ArrayList *inputL = fromArray(input, 5);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 8);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test9Phase2() {
  // Phase 1
  struct Instruction phase1_expected[8] = {
    CreateLui_lab(1, 0x0FFF, "label9"), // label1: lui $t0, 0x0FFF
    CreateOri(1, 1, 0xFFFF), // ori $at, $at, 0xFFFF
    CreateAddu(8, 0, 1),  // addu $t0,$at,$zero
    CreateSlt(9, 0, 8),     // slt $t1,$zero,$t1
    CreateOr_lab(10, 9, 8, "label5"), // label5: or $t2, $t1, $t0
    CreateSlt(1, 8, 0), // slt $at, $zero, $t0
    CreateBeq(1, 0, "label5"), // bne $at,$zero,label5
    CreateOri(11, 8, 10) // ori $t3,$t0,10 
  };

  // Phase 2
  struct Instruction phase2_expected[8] = {
    CreateLui_lab(1, 0x0FFF, "label9"), // label1: lui $t0, 0x0FFF
    CreateOri(1, 1, 0xFFFF), // ori $at, $at, 0xFFFF
    CreateAddu(8, 0, 1),  // addu $t0,$at,$zero
    CreateSlt(9, 0, 8),     // slt $t1,$zero,$t1
    CreateOr_lab(10, 9, 8, "label5"), // label5: or $t2, $t1, $t0
    CreateSlt(1, 8, 0), // slt $at, $zero, $t0
    CreateBeq_imm(1, 0, -3), // bne $at,$zero,label5
    CreateOri(11, 8, 10) // ori $t3,$t0,10
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 8);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 8);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test9Phase3() {
  // Phase 2
  struct Instruction phase2_expected[8] = {
    CreateLui_lab(1, 0x0FFF, "label9"), // label1: lui $t0, 0xF
    CreateOri(1, 1, 0xFFFF), // ori $at, $at, 0xFFFFFF
    CreateAddu(8, 0, 1),  // addu $t0,$at,$zero
    CreateSlt(9, 0, 8),     // slt $t1,$zero,$t1
    CreateOr_lab(10, 9, 8, "label5"), // label5: or $t2, $t1, $t0
    CreateSlt(1, 8, 0), // slt $at, $zero, $t0
    CreateBeq_imm(1, 0, -3), // bne $at,$zero,label5
    CreateOri(11, 8, 10) // ori $t3,$t0,10
  };

  // Phase 3
  uint32_t phase3_expected[8] = {
    // HINT: to get these, type the input program into MARS, assemble, and copy the binary values into your test case
    0x3c010fff,
    0x3421ffff,
    0x00014021,
    0x0008482a,
    0x01285025,
    0x0100082a,
    0x1020fffd,
    0x350b000a
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 8);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}
        
void test10Phase1() {
  struct Instruction input[6] = {
    //for labeling purposes for bge to possibly branch to
    CreateAddu_lab(8, 0, 0, "label1"),
    //addiu $s0, $0, 0xF
    //testing for an immediate that is within 16-bit range
    CreateAddiu(16, 0, 0xF),
    //for labeling purposes and also to test out OR
    //or $s3, $t2, $t8
    CreateOr_lab(19, 10, 24, "label2"),
    //addiu $s1, $0, 0xFFFFFFF1 or -15
    //testing for an immediate that is negative and within range
    CreateAddiu(17, 0, 0xFFFFFFF1),
    //ori $s2, $0, Ox0ABC0000
    //testing for ori with an outside range positive immediate
    CreateOri(18, 18, 0x0ABC0000),
    //test the other MAL instruction of bge along with branching to the second label rather than the first
    //bge  $s3, $t1, label12
    CreateBge(19, 9, "label2")
  };
  // Phase 1
  struct Instruction phase1_expected[9] = {
    CreateAddu_lab(8, 0, 0, "label1"),
    CreateAddiu(16, 0, 0xF),
    CreateOr_lab(19, 10, 24, "label2"), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateAddiu(17, 0, 0xFFFFFFF1),
    CreateLui(1, 0x0ABC), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateOri(1, 1, 0), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateOr(18, 18, 1), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateSlt(1, 19, 9),  //new instructions for bge  $s3, $t1, label12
    CreateBeq(1, 0, "label2"),  //new instructions for bge  $s3, $t1, label12
  };

  struct ArrayList *inputL = fromArray(input, 6);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 9);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}
        
void test10Phase2() {
  // Phase 1
  struct Instruction phase1_expected[9] = {
    CreateAddu_lab(8, 0, 0, "label1"),
    CreateAddiu(16, 0, 0xF),
    CreateOr_lab(19, 10, 24, "label2"), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateAddiu(17, 0, 0xFFFFFFF1),
    CreateLui(1, 0x0ABC), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateOri(1, 1, 0), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateOr(18, 18, 1), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateSlt(1, 19, 9),  //new instructions for bge  $s3, $t1, label12
    CreateBeq(1, 0, "label2"),  //new instructions for bge  $s3, $t1, label12
  };

  // Phase 2
  struct Instruction phase2_expected[9] = {
    CreateAddu_lab(8,0, 0, "label1"),
    CreateAddiu(16, 0, 0xF),
    CreateOr_lab(19, 10, 24, "label2"),
    CreateAddiu(17, 0, 0xFFFFFFF1),
    CreateLui(1, 0x0ABC), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateOri(1, 1, 0), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateOr(18, 18, 1), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateSlt(1, 19, 9), //new instructions for bge  $s3, $t1, label12
    CreateBeq_imm(1, 0, -7)  //new instructions for bge  $s3, $t1, label12, immediate = -7
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 9);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 9);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}
        
void test10Phase3() {
  // Phase 2
  struct Instruction phase2_expected[9] = {
    CreateAddu_lab(8,0, 0, "label1"),
    CreateAddiu(16, 0, 0xF),
    CreateOr_lab(19, 10, 24, "label2"),
    CreateAddiu(17, 0, 0xFFFFFFF1),
    CreateLui(1, 0x0ABC), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateOri(1, 1, 0x0000), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateOr(18, 18, 1), //new instructions for ori $s2, $0, Ox0ABC0000
    CreateSlt(1, 19, 9), //new instructions for bge  $s3, $t1, label12
    CreateBeq_imm(1, 0, -7)  //new instructions for bge  $s3, $t1, label12, immediate = -7
  };

  // Phase 3
  uint32_t phase3_expected[9] = {
    0x00004021, //label 1
    0x2410000F, //small immediate
    0x01589825, //label 2
    0x2411FFF1, //negative immediate
    0x3C010ABC, //new instructions for ori $s2, $0, Ox0ABC0000
    0x34210000, //new instructions for ori $s2, $0, Ox0ABC0000
    0x02419025, //new instructions for ori $s2, $0, Ox0ABC0000
    0x0269082a, //new instructions for bge  $s3, $t1, label12
    0x1020FFF9 //new instructions for bge  $s3, $t1, label12
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 9);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}


void test11Phase1() {
  struct Instruction input[2] = {
    CreateSll(2,3,10),
    CreateAddiu(2, 3, 0xFFFF7FFF)
  };
  // Phase 1
  struct Instruction phase1_expected[4] = {
    CreateSll(2,3,10),
    CreateLui(1, 0xFFFF),
    CreateOri(1, 1, 0x7FFF),
    CreateAddu(2, 3, 1)
  };

  struct ArrayList *inputL = fromArray(input, 2);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 4);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}

void test11Phase2() {
  // Phase 1
  struct Instruction phase1_expected[4] = {
    CreateSll(2,3,10),
    CreateLui(1, 0xFFFF),
    CreateOri(1, 1, 0x7FFF),
    CreateAddu(2, 3, 1)
  };

  // Phase 2
  struct Instruction phase2_expected[4] = {
    CreateSll(2,3,10),
    CreateLui(1, 0xFFFF),
    CreateOri(1, 1, 0x7FFF),
    CreateAddu(2, 3, 1)
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 4);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 4);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}

void test11Phase3() {
  // Phase 2
  struct Instruction phase2_expected[4] = {
    CreateSll(2,3,10),
    CreateLui(1, 0xFFFF),
    CreateOri(1, 1, 0x7FFF),
    CreateAddu(2, 3, 1)
  };

  // Phase 3
  uint32_t phase3_expected[4] = {
    0x00031280,
    0x3c01ffff,
    0x34217fff,
    0x00611021
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 4);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}

void test12Phase1() {
  struct Instruction input[1] = {
    CreateOri(8, 16, 0xFFFFFFF0)
  };
  // Phase 1
  struct Instruction phase1_expected[3] = {
    CreateLui(1, 0xFFFF),
    CreateOri(1, 1, 0xFFF0),
    CreateOr(8, 16, 1)
  };

  struct ArrayList *inputL = fromArray(input, 1);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 3);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}

void test12Phase2() {
  // Phase 1
  struct Instruction phase1_expected[3] = {
    CreateLui(1, 0xFFFF),
    CreateOri(1, 1, 0xFFF0),
    CreateOr(8, 16, 1)
  };

  // Phase 2
  struct Instruction phase2_expected[3] = {
    CreateLui(1, 0xFFFF),
    CreateOri(1, 1, 0xFFF0),
    CreateOr(8, 16, 1)
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 3);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 3);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}

void test12Phase3() {
  // Phase 2
  struct Instruction phase2_expected[3] = {
    CreateLui(1, 0xFFFF),
    CreateOri(1, 1, 0xFFF0),
    CreateOr(8, 16, 1)
  };

  // Phase 3
  uint32_t phase3_expected[3] = {
    0x3c01ffff,
    0x3421fff0,
    0x02014025
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 3);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}

void test13Phase1() {
  struct Instruction input[2] = {
    CreateMove(8, 16),
    CreateMove(17, 9)
  };
  // Phase 1
  struct Instruction phase1_expected[2] = {
    CreateAddu(8, 0, 16),
    CreateAddu(17, 0, 9)
  };

  struct ArrayList *inputL = fromArray(input, 2);
  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 2);

  testHelperPhase1(inputL, phase1_expectedL);

  freeList(inputL);
  freeList(phase1_expectedL);
}

void test13Phase2() {
  // Phase 1
  struct Instruction phase1_expected[2] = {
    CreateAddu(8, 0, 16),
    CreateAddu(17, 0, 9)
  };

  // Phase 2
  struct Instruction phase2_expected[2] = {
    CreateAddu(8, 0, 16),
    CreateAddu(17, 0, 9)
  };

  struct ArrayList *phase1_expectedL = fromArray(phase1_expected, 2);
  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 2);

  testHelperPhase2(phase1_expectedL, phase2_expectedL);

  freeList(phase1_expectedL);
  freeList(phase2_expectedL);
}

void test13Phase3() {
  // Phase 2
  struct Instruction phase2_expected[2] = {
    CreateAddu(8, 0, 16),
    CreateAddu(17, 0, 9)
  };

  // Phase 3
  uint32_t phase3_expected[2] = {
    0x00104021,
    0x00098821
  };

  struct ArrayList *phase2_expectedL = fromArray(phase2_expected, 2);
  testHelperPhase3(phase2_expectedL, phase3_expected);
  freeList(phase2_expectedL);
}

int main() {
  test1Phase1();
  test1Phase2();
  test1Phase3();

  test2Phase1();
  test2Phase2();
  test2Phase3();

  test3Phase1();
  test3Phase2();
  test3Phase3();

  test4Phase1();
  test4Phase2();
  test4Phase3();

  test5Phase1();
  test5Phase2();
  test5Phase3();

  test6Phase1();
  test6Phase2();
  test6Phase3();

  test7Phase1();
  test7Phase2();
  test7Phase3();

  test8Phase1();
  test8Phase2();
  test8Phase3();

  test9Phase1();
  test9Phase2();
  test9Phase3();

  test10Phase1();
  test10Phase2();
  test10Phase3();

  test11Phase1();
  test11Phase2();
  test11Phase3();

  test12Phase1();
  test12Phase2();
  test12Phase3();

  test13Phase1();
  test13Phase2();
  test13Phase3();
}


/*
        @Test(expected =AssemblerException.class)
        public void testShiftTooSmall() {
            CreateSll(0, 0, -1);
        }
        @Test(expected =AssemblerException.class)
        public void testShiftTooBig() {
            CreateSll(0, 0, 32);
        }
        @Test(expected =AssemblerException.class)
        public void testRdTooSmall() {
            CreateSll(-2, 0, 0);
        }
        @Test(expected =AssemblerException.class)
        public void testRdTooBig() {
            CreateSll(32, 0, 0);
        }
*/

