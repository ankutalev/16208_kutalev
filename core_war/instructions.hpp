//
// Created by ulyssess on 24.10.17.
//

#ifndef CORE_WAR_INSTRUCTIONS_HPP
#define CORE_WAR_INSTRUCTIONS_HPP
#include <vector>
#include <iostream>
#include "CircularBuffer.hpp"

enum class Mods :char{
            Lattice = '#',
            Dollar = '$',
            Dog = '@',
            Star ='*' ,
            Less = '<',
            More = '>',
            Open ='{',
            Close ='}',
            Not = ' '
};
enum class Modifiers :int   { A = 1, B =2, AB=3, BA=4, F=5, X=6, I=7, Not=0};
/*enum class Opcodes : int {
    DAT = 0,
    MOV = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    MOD = 6,
    JMP = 7,
    JMZ = 8,
    JMN = 9,
    DJN = 10,
    SEQ = 12,
    SNE = 13,
    SLT = 14,
    SPL = 15,
    NOP = 16,
    ORG
}; */

struct Instruction {
public:
    Instruction(): OpcodeMod(Modifiers::Not) {}
    virtual void Execution (std::vector<Instruction*>&,CircularBuffer&,CircularBuffer::Iterator&){std::cout<<"gde ya...";}//std::cout<<"gde ya...";}
    size_t GettingCode(unsigned i) {
       // if(Body== Opcodes::DAT&& AOperand==0&& BOperand==0)
      //      return 0;
            std::cout<< static_cast<int>(OpcodeMod)<< static_cast<char>(AOperandMod)<<AOperand << static_cast<char>(BOperandMod) << BOperand<<"  "<<i<<std::endl ;
        return 0;
    }
    void SetOffset (std::vector<Instruction*>& Core, CircularBuffer::Iterator& it, int size,Mods ModAorB,int Operand, int* AorB) {
        int tmp = (Operand+(*it).Address)%size;
        if(tmp<0)
            tmp+=size;
        switch(ModAorB) {

            case (Mods::Lattice):
                *AorB = 0;
                break;
            case (Mods :: Star):
                *AorB = Core[tmp]->AOperand %size;
                break;
            case (Mods::Dog):
                *AorB = Core[tmp]->BOperand% size;
                break;
            case (Mods::Open):
                Core[tmp]->AOperand--;
                *AorB = (Core[tmp]->AOperand)% size;
                break;
            case (Mods ::Close):
                *AorB = (Core[tmp]->AOperand)% size;
                Core[tmp]->AOperand++;
                break;
            case (Mods::More):
                *AorB = (Core[tmp]->BOperand)% size;
                Core[tmp]->BOperand++;
                break;
            case (Mods::Less):
                Core[tmp]->BOperand--;
                *AorB = (Core[tmp]->BOperand)% size;
                break;
            case (Mods::Dollar):
            case (Mods :: Not):
                *AorB = Operand;
                break;
         }
        *AorB = (*AorB + (*it).Address)%size;
        if(*AorB<0)
            (*AorB)+=size;
    }
    void SetOffsets (std::vector<Instruction*>& Core, CircularBuffer::Iterator& it, size_t size) {
        SetOffset(Core,it,size,AOperandMod,AOperand,&AOffset);
        SetOffset(Core,it,size,BOperandMod,BOperand,&BOffset);
    }
    Instruction (const Instruction& in) {
        OpcodeMod = in.OpcodeMod;
        AOperand = in.AOperand;
        BOperand = in.BOperand;
        AOperandMod = in.AOperandMod;
        BOperandMod = in.BOperandMod;
        AOffset = in.AOffset;
        BOffset = in.BOffset;
    }
    virtual Instruction* Clone() {
        return new Instruction(*this);
    }
    static bool IsModAllowed (char c) {
        const char allowed [8] = {'@','*','$','#','{','}','>','<'};
        for (char i : allowed)
            if (c== i)
                return true;
        return false;
    }
    virtual ~Instruction() {}
    Modifiers OpcodeMod;
    Mods AOperandMod;
    Mods BOperandMod;
    int AOperand;
    int BOperand;
protected:
    int AOffset;
    int BOffset;
};


#endif //CORE_WAR_INSTRUCTIONS_HPP
