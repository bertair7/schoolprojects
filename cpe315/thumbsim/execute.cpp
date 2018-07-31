/* Austin McInnis, Ryan Blair */

#include "thumbsim.hpp"
// These are just the register NUMBERS
#define PC_REG 15  
#define LR_REG 14
#define SP_REG 13

// These are the contents of those registers
#define PC rf[PC_REG]
#define LR rf[LR_REG]
#define SP rf[SP_REG]

Stats stats;
Caches caches(0);

// CPE 315: you'll need to implement some custom sign-extension functions
// in addition to the ones given below, particularly for the unconditional
// branch instruction, which has an 11-bit immediate field
unsigned int signExtend16to32ui(short i) {
  return static_cast<unsigned int>(static_cast<int>(i));
}

unsigned int signExtend8to32ui(char i) {
  return static_cast<unsigned int>(static_cast<int>(i));
}

unsigned int signExtend11to32ui(short i) {
  if (i & 0x400) {
     i ^= 0xFFFFF800;
  }
  return static_cast<unsigned int>(static_cast<int>(i));
}

ASPR flags;

// CPE 315: You need to implement a function to set the Negative and Zero
// flags for each instruction that does that. It only needs to take
// one parameter as input, the result of whatever operation is executing
void setNegativeZero (int result) {
    if (result == 0) {
        flags.Z = 1;
    }
    else {
        flags.Z = 0;
    }
    if (result < 0) {
        flags.N = 1;
    }
    else {
        flags.N = 0;
    }
}
// This function is complete, you should not have to modify it
void setCarryOverflow (int num1, int num2, OFType oftype) {
  switch (oftype) {
    case OF_ADD:
      if (((unsigned long long int)num1 + (unsigned long long int)num2) ==
          ((unsigned int)num1 + (unsigned int)num2)) {
        flags.C = 0;
      }
      else {
        flags.C = 1;
      }
      if (((long long int)num1 + (long long int)num2) ==
          ((int)num1 + (int)num2)) {
        flags.V = 0;
      }
      else {
        flags.V = 1;
      }
      break;
    case OF_SUB:
      if (num1 >= num2) {
        flags.C = 1;
      }
      else if (((unsigned long long int)num1 - (unsigned long long int)num2) ==
          ((unsigned int)num1 - (unsigned int)num2)) {
        flags.C = 0;
      }
      else {
        flags.C = 1;
      }
      if (((num1==0) && (num2==0)) ||
          (((long long int)num1 - (long long int)num2) ==
           ((int)num1 - (int)num2))) {
        flags.V = 0;
      }
      else {
        flags.V = 1;
      }
      break;
    case OF_SHIFT:
      // C flag unaffected for shifts by zero
      if (num2 != 0) {
        if (((unsigned long long int)num1 << (unsigned long long int)num2) ==
            ((unsigned int)num1 << (unsigned int)num2)) {
          flags.C = 0;
        }
        else {
          flags.C = 1;
        }
      }
      // Shift doesn't set overflow
      break;
    default:
      cerr << "Bad OverFlow Type encountered." << __LINE__ << __FILE__ << endl;
      exit(1);
  }
}

// CPE 315: You're given the code for evaluating BEQ, and you'll need to 
// complete the rest of these conditions. See Page 99 of the armv6 manual
static int checkCondition(unsigned short cond) {
  switch(cond) {
    case EQ:
      if (flags.Z == 1) {
        return TRUE;
      }
      break;
    case NE:
      if (flags.Z == 0) {
        return TRUE;
      }
      break;
    case CS:
      if (flags.C == 1) {
        return TRUE;
      }
      break;
    case CC:
      if (flags.C == 0) {
        return TRUE;
      }
      break;
    case MI:
      if (flags.N == 1) {
        return TRUE;
      }
      break;
    case PL:
      if (flags.N == 0) {
        return TRUE;
      }
      break;
    case VS:
      if (flags.V == 1) {
        return TRUE;
      }
      break;
    case VC:
      if (flags.V == 0) {
        return TRUE;
      }
      break;
    case HI:
      if ((flags.C == 1) && (flags.Z == 0)) {
        return TRUE;
      }
      break;
    case LS:
      if ((flags.C == 0) || (flags.Z == 1)) {
        return TRUE;
      }
      break;
    case GE:
      if (flags.N == flags.V) {
        return TRUE;
      }
      break;
    case LT:
      if (flags.N != flags.V) {
        return TRUE;
      }
      break;
    case GT:
      if ((flags.Z == 0) && (flags.N == flags.V)) {
        return TRUE;
      }
      break;
    case LE:
      if ((flags.Z == 1) || (flags.N != flags.V)) {
        return TRUE;
      }
      break;
    case AL:
      return TRUE;
      break;
  }
  return FALSE;
}

void execute() {
  Data16 instr = imem[PC];
  Data16 instr2;
  Data32 temp(0);
  Thumb_Types itype;
  unsigned int pctarget = PC + 2;
  unsigned int addr;
  int i, n, offset;
  unsigned int list, mask;
  int num1, num2, result, BitCount;
  unsigned int bit;

  /* Convert instruction to correct type */
  BL_Type blupper(instr);
  ALU_Type alu(instr);
  SP_Type sp(instr);
  DP_Type dp(instr);
  LD_ST_Type ld_st(instr);
  MISC_Type misc(instr);
  COND_Type cond(instr);
  UNCOND_Type uncond(instr);
  LDM_Type ldm(instr);
  STM_Type stm(instr);
  LDRL_Type ldrl(instr);
  ADD_SP_Type addsp(instr);

  BL_Ops bl_ops;
  ALU_Ops add_ops;
  DP_Ops dp_ops;
  SP_Ops sp_ops;
  LD_ST_Ops ldst_ops;
  MISC_Ops misc_ops;

  rf.write(PC_REG, pctarget);
  stats.numRegWrites += 1; 
  stats.numRegReads += 1;

  itype = decode(ALL_Types(instr));
  stats.instrs++;

  // CPE 315: The bulk of your work is in the following switch statement
  // All instructions will need to have stats and cache access info added
  // as appropriate for that instruction.
  switch(itype) {
    case ALU:
      add_ops = decode(alu);
      switch(add_ops) {
        case ALU_LSLI:
	  setCarryOverflow(rf[alu.instr.lsli.rm], alu.instr.lsli.imm, OF_SHIFT);  
          result = rf[alu.instr.lsli.rm] << alu.instr.lsli.imm;
	  /*n = log2(rf[alu.instr.lsli.rm]);
          while ((bit = log2(result)) > n) {
	     result -= pow(2, bit);
	  }*/
	  rf.write(alu.instr.lsli.rd, result);
	  setNegativeZero(result);
          stats.numRegReads += 1;
          stats.numRegWrites += 1; 
	  break;
        case ALU_ADDR:
	  //COMPLETE
          setCarryOverflow(rf[alu.instr.addr.rn], rf[alu.instr.addr.rm], OF_ADD);  
          rf.write(alu.instr.addr.rd, rf[alu.instr.addr.rn] + rf[alu.instr.addr.rm]);
          setNegativeZero(rf[alu.instr.addr.rd]);
          stats.numRegReads += 2;
          stats.numRegWrites += 1; 
          break;
        case ALU_SUBR:
          setCarryOverflow(rf[alu.instr.subr.rn], rf[alu.instr.subr.rm], OF_SUB);  
          rf.write(alu.instr.subr.rd, rf[alu.instr.subr.rn] - rf[alu.instr.subr.rm]);
          setNegativeZero(rf[alu.instr.subr.rd]);
          stats.numRegReads += 2;
          stats.numRegWrites += 1; 
          break;
        case ALU_ADD3I:
	  //COMPLETE
          setCarryOverflow(rf[alu.instr.add3i.rn], alu.instr.add3i.imm, OF_ADD);  
          rf.write(alu.instr.add3i.rd, rf[alu.instr.add3i.rn] + alu.instr.add3i.imm);
          setNegativeZero(rf[alu.instr.add3i.rd]);
          stats.numRegReads += 1;
          stats.numRegWrites += 1; 
          break;
        case ALU_SUB3I:
          setCarryOverflow(rf[alu.instr.sub3i.rn], alu.instr.sub3i.imm, OF_SUB);  
          rf.write(alu.instr.sub3i.rd, rf[alu.instr.sub3i.rn] - alu.instr.sub3i.imm);
          setNegativeZero(rf[alu.instr.sub3i.rd]);
          stats.numRegReads += 1;
          stats.numRegWrites += 1; 
          break;
        case ALU_MOV:
          //COMPLETE
          rf.write(alu.instr.mov.rdn, alu.instr.mov.imm);
          setNegativeZero(alu.instr.mov.imm);
          stats.numRegWrites += 1; 
          break;
        case ALU_CMP:
	  //COMPLETE
          result = rf[alu.instr.cmp.rdn] - alu.instr.cmp.imm;
          setCarryOverflow(rf[alu.instr.cmp.rdn], alu.instr.cmp.imm, OF_SUB);  
          setNegativeZero(result);
          stats.numRegReads += 1;
          break;
        case ALU_ADD8I:
          setCarryOverflow(rf[alu.instr.add8i.rdn], alu.instr.add8i.imm, OF_ADD);  
          rf.write(alu.instr.add8i.rdn, rf[alu.instr.add8i.rdn] + alu.instr.add8i.imm);
          setNegativeZero(rf[alu.instr.add8i.rdn]);
          stats.numRegReads += 1;
          stats.numRegWrites += 1; 
          break;
        case ALU_SUB8I:
          setCarryOverflow(rf[alu.instr.sub8i.rdn], alu.instr.sub8i.imm, OF_SUB);  
          rf.write(alu.instr.sub8i.rdn, rf[alu.instr.sub8i.rdn] - alu.instr.sub8i.imm);
          setNegativeZero(rf[alu.instr.sub8i.rdn]);
          stats.numRegReads += 1;
          stats.numRegWrites += 1; 
          break;
        default:
          break;
      }
      break;
    case BL: 
      // This instruction is complete, nothing needed here
      bl_ops = decode(blupper);
      if (bl_ops == BL_UPPER) {
        // PC has already been incremented above
        instr2 = imem[PC];
        BL_Type bllower(instr2);
        if (blupper.instr.bl_upper.s) {
          addr = static_cast<unsigned int>(0xff<<24) | 
            ((~(bllower.instr.bl_lower.j1 ^ blupper.instr.bl_upper.s))<<23) |
            ((~(bllower.instr.bl_lower.j2 ^ blupper.instr.bl_upper.s))<<22) |
            ((blupper.instr.bl_upper.imm10)<<12) |
            ((bllower.instr.bl_lower.imm11)<<1);
        }
        else {
          addr = ((blupper.instr.bl_upper.imm10)<<12) |
            ((bllower.instr.bl_lower.imm11)<<1);
        }
        // return address is 4-bytes away from the start of the BL insn
        rf.write(LR_REG, PC + 2);
        // Target address is also computed from that point
        rf.write(PC_REG, PC + 2 + addr);

        stats.numRegReads += 1;
        stats.numRegWrites += 2; 
      }
      else {
        cerr << "Bad BL format." << endl;
        exit(1);
      }
      break;
    case DP:
      dp_ops = decode(dp);
      switch(dp_ops) {
        case DP_RSB:
	  setCarryOverflow(0, rf[dp.instr.DP_Instr.rm], OF_SUB);
	  result = 0 - rf[dp.instr.DP_Instr.rm];
	  setNegativeZero(result);
	  rf.write(dp.instr.DP_Instr.rdn, result);
          stats.numRegReads += 1;
          stats.numRegWrites += 1; 
	  break;
	case DP_CMP:
	  result = rf[dp.instr.DP_Instr.rdn] - rf[dp.instr.DP_Instr.rm];
	  setCarryOverflow(rf[dp.instr.DP_Instr.rdn], rf[dp.instr.DP_Instr.rm], OF_SUB);
	  setNegativeZero(result);
	  stats.numRegReads += 2;
	  break;
      }
      break;
    case SPECIAL:
      sp_ops = decode(sp);
      switch(sp_ops) {
        case SP_MOV:
	  //COMPLETE
          if (sp.instr.mov.d) {
            //rf.write(SP_REG, rf[sp.instr.mov.rm]);
            rf.write(sp.instr.mov.rd+8, rf[sp.instr.mov.rm]);
          }
          else {
            rf.write(sp.instr.mov.rd, rf[sp.instr.mov.rm]);
          }
	  setNegativeZero(rf[sp.instr.mov.rm]);
          stats.numRegWrites += 1; 
          stats.numRegReads += 1;
          break;
        case SP_ADD:
          if (sp.instr.add.d) {
	     setCarryOverflow(rf[sp.instr.add.rd+8], rf[sp.instr.add.rm], OF_ADD);
             rf.write(sp.instr.add.rd, rf[sp.instr.add.rd+8] + rf[sp.instr.add.rm]);
             setNegativeZero(rf[sp.instr.add.rd+8]);
	  }
	  else {
             setCarryOverflow(rf[sp.instr.add.rd], rf[sp.instr.add.rm], OF_ADD);
             rf.write(sp.instr.add.rd, rf[sp.instr.add.rd] + rf[sp.instr.add.rm]);
             setNegativeZero(rf[sp.instr.add.rd]);
	  }
          stats.numRegReads += 2;
          stats.numRegWrites++;
          break;
        case SP_CMP:
	  if (sp.instr.cmp.d) {
	     setCarryOverflow(rf[sp.instr.cmp.rd+8], rf[sp.instr.cmp.rm], OF_SUB);
	     result = rf[sp.instr.cmp.rd+8] - rf[sp.instr.cmp.rm];
	  }
	  else {
	     setCarryOverflow(rf[sp.instr.cmp.rd], rf[sp.instr.cmp.rm], OF_SUB);
	     result = rf[sp.instr.cmp.rd] - rf[sp.instr.cmp.rm];
	  }
	  setNegativeZero(result);
	  stats.numRegReads += 2;
          break;
      }
      break;
    case LD_ST:
      // You'll want to use these load and store models
      // to implement ldrb/strb, ldm/stm and push/pop
      ldst_ops = decode(ld_st);
      switch(ldst_ops) {
        case STRI:
	  //COMPLETE
          addr = rf[ld_st.instr.ld_st_imm.rn] + ld_st.instr.ld_st_imm.imm * 4;
          dmem.write(addr, rf[ld_st.instr.ld_st_imm.rt]);
          caches.access(addr);
          stats.numRegReads += 2;
          stats.numMemWrites += 1;
	  break;
        case LDRI:
	  //COMPLETE
          addr = rf[ld_st.instr.ld_st_imm.rn] + ld_st.instr.ld_st_imm.imm * 4;
          rf.write(ld_st.instr.ld_st_imm.rt, dmem[addr]);
          caches.access(addr);
          stats.numRegReads += 1;
          stats.numRegWrites += 1;
	  stats.numMemReads += 1; 
          break;
        case STRR:
	  //COMPLETE
          addr = rf[ld_st.instr.ld_st_reg.rn] + rf[ld_st.instr.ld_st_reg.rm];
          dmem.write(addr, rf[ld_st.instr.ld_st_reg.rt]);
          caches.access(addr);
          stats.numRegReads += 3;
          stats.numMemWrites += 1;
          break;
        case LDRR:
	  //COMPLETE
          addr = rf[ld_st.instr.ld_st_reg.rn] + rf[ld_st.instr.ld_st_reg.rm];
          rf.write(ld_st.instr.ld_st_reg.rt, dmem[addr]); 
          caches.access(addr);
          stats.numRegReads += 2;
          stats.numRegWrites += 1; 
	  stats.numMemReads += 1; 
          break;
        case STRBI:
	  addr = rf[ld_st.instr.ld_st_imm.rn] + ld_st.instr.ld_st_imm.imm *4;
	  temp = dmem[addr];
          caches.access(addr);
	  temp.set_data_ubyte4(0, rf[ld_st.instr.ld_st_imm.rt] & 0xff);
	  dmem.write(addr, temp);
          caches.access(addr);
          //numRegReads += 1? Compare to STRI
	  stats.numRegReads += 2;
	  stats.numMemReads += 1; 
          stats.numMemWrites += 1;
	  break;
	case LDRBI:
	  addr = rf[ld_st.instr.ld_st_imm.rn] + ld_st.instr.ld_st_imm.imm *4;
	  temp = dmem[addr];
	  caches.access(addr);
	  rf.write(ld_st.instr.ld_st_imm.rt, temp.data_ubyte4(0)); 	  	  
          caches.access(addr);
          stats.numRegReads += 1;
          stats.numRegWrites += 1; 
	  stats.numMemReads += 1; 
	  break;
        case STRBR:
          addr = rf[ld_st.instr.ld_st_reg.rn] + rf[ld_st.instr.ld_st_reg.rm];
          temp = dmem[addr];
          caches.access(addr);
          temp.set_data_ubyte4(0, rf[ld_st.instr.ld_st_reg.rt] & 0xff);
          dmem.write(addr, temp);
          caches.access(addr);
          stats.numRegReads += 3;
          stats.numMemReads += 1;
          stats.numMemWrites += 1;
          break;
        case LDRBR:
	  addr = rf[ld_st.instr.ld_st_reg.rn] + rf[ld_st.instr.ld_st_reg.rm];
	  temp = dmem[addr];
	  rf.write(ld_st.instr.ld_st_imm.rt, temp.data_ubyte4(0)); 	  	  
          caches.access(addr);
          stats.numRegReads += 2;
          stats.numRegWrites += 1; 
	  stats.numMemReads += 1; 
          break;
      }
      break;
    case MISC:
      misc_ops = decode(misc);
      switch(misc_ops) {
        case MISC_PUSH:
	  //COMPLETE
          BitCount = 0;
          bit = 1;
          for (int i = 0; i < 8; i++) {
              if (misc.instr.push.reg_list & bit) {
                  BitCount++;
              }
              bit = bit * 2;
          }
          
          if (misc.instr.push.m) {
              BitCount++;
          }
          
          addr = SP - BitCount*4;
          bit = 1;
          for (int j = 0; j < 8; j++) {
              if(misc.instr.push.reg_list & bit) {
                dmem.write(addr, rf[j]);
                caches.access(addr);
                addr += 4;
                stats.numRegReads++;
          	stats.numMemWrites += 1;
              }
              bit = bit * 2;
          }

          if (misc.instr.push.m) {
              dmem.write(addr, LR);
              caches.access(addr);
              addr += 4;
              stats.numMemWrites += 1;
              stats.numRegReads++;
          }

          rf.write(SP_REG, SP - 4*BitCount);
          stats.numRegWrites += 1; 
          stats.numRegReads += 1; 
          break;
        case MISC_POP:
	  //COMPLETE
          addr = SP;
          bit = 1;
          BitCount = 0;
          for (int i = 0; i < 8; i++) {
              if (misc.instr.pop.reg_list & bit) {
                 BitCount++;
                 rf.write(i, dmem[addr]);
                 stats.numRegWrites += 1; 
	  	 stats.numMemReads += 1; 
                 caches.access(addr);
                 addr += 4;
              }
              bit = bit * 2;
          }
          if (misc.instr.pop.m) {
             BitCount++;
             rf.write(PC_REG, dmem[addr]);
             stats.numRegWrites += 1; 
	     stats.numMemReads += 1; 
             caches.access(addr);
          }
          rf.write(SP_REG, SP + 4*BitCount);
          stats.numRegWrites += 1; 
          stats.numRegReads += 1; 
          break;
        case MISC_SUB:
	  //COMPLETE
          rf.write(SP_REG, SP - (misc.instr.sub.imm*4));
          stats.numRegWrites += 1; 
          stats.numRegReads += 1; 
          break;
        case MISC_ADD:
	  //COMPLETE
          rf.write(SP_REG, SP + (misc.instr.add.imm*4));
          stats.numRegWrites += 1; 
          stats.numRegReads += 1; 
          break;
      }
      break;
    case COND:
      decode(cond);
      // Once you've completed the checkCondition function,
      // this should work for all your conditional branches.
      if (checkCondition(cond.instr.b.cond)){
        rf.write(PC_REG, PC + 2 * signExtend8to32ui(cond.instr.b.imm) + 2);
        stats.numRegWrites += 1; 
        stats.numRegReads += 1;
        if ((signed int)signExtend8to32ui(cond.instr.b.imm) < 0) {
          stats.numBackwardBranchesTaken += 1;
        }
        else {
          stats.numForwardBranchesTaken += 1;
        }
      }
      else {
        if ((signed int)signExtend8to32ui(cond.instr.b.imm) < 0)
          stats.numBackwardBranchesNotTaken += 1;
        else
          stats.numForwardBranchesNotTaken += 1;
      }
      break;
    case UNCOND:
      // Essentially the same as the conditional branches, but with no
      // condition check, and a different sized immediate field
      decode(uncond);
      rf.write(PC_REG, PC + 2 * signExtend11to32ui(uncond.instr.b.imm) + 2);
      stats.numRegWrites += 1; 
      stats.numRegReads += 1;
      break;
    case LDM:
      decode(ldm);
      addr = rf[ldm.instr.ldm.rn];
      bit = 1;
      for (int i = 0; i < 8; i++) {
	 if (ldm.instr.ldm.reg_list & bit) {
	    rf.write(i, dmem[addr]);
            caches.access(addr);
	    addr += 4;
            stats.numRegWrites += 1; 
	    stats.numMemReads += 1; 
	 }
	 bit *= 2;
      }
      rf.write(ldm.instr.ldm.rn, addr);
      stats.numRegWrites++;
      stats.numRegReads++;
      break;
    case STM:
      decode(stm);
      addr = rf[stm.instr.stm.rn];
      bit = 1;
      for (int i = 0; i < 8; i++) {
	 if (stm.instr.stm.reg_list & bit) {
	    dmem.write(addr, rf[i]);
            caches.access(addr);
	    addr += 4;
            stats.numRegReads++;
            stats.numMemWrites += 1;
	 }
	 bit *= 2;
      }
      rf.write(stm.instr.stm.rn, addr);
      stats.numRegReads++;
      stats.numRegWrites++;
      break;
    case LDRL:
      // This instruction is complete, nothing needed
      decode(ldrl);
      // Need to check for alignment by 4
      if (PC & 2) {
        addr = PC + 2 + (ldrl.instr.ldrl.imm)*4;
      }
      else {
        addr = PC + (ldrl.instr.ldrl.imm)*4;
      }
      // Requires two consecutive imem locations pieced together
      temp = imem[addr] | (imem[addr+2]<<16);  // temp is a Data32
      rf.write(ldrl.instr.ldrl.rt, temp);

      // One write for updated reg
      stats.numRegWrites++;
      // One read of the PC
      stats.numRegReads++;
      // One mem read, even though it's imem, and there's two of them
      stats.numMemReads++;
      break;
    case ADD_SP:
      //COMPLETE
      decode(addsp);
      rf.write(addsp.instr.add.rd, SP + (addsp.instr.add.imm*4));
      setCarryOverflow(SP, addsp.instr.add.imm*4, OF_ADD);
      setNegativeZero(rf[addsp.instr.add.rd]); 
      stats.numRegWrites += 1; 
      stats.numRegReads += 1; 
      break;
    default:
      cout << "[ERROR] Unknown Instruction to be executed" << endl;
      exit(1);
      break;
  }
}
