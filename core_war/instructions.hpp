//
// Created by ulyssess on 24.10.17.
//

#ifndef CORE_WAR_INSTRUCTIONS_HPP
#define CORE_WAR_INSTRUCTIONS_HPP
#include <vector>
#include <iostream>
#include "CircularBuffer.hpp"

struct zaglushka {
    int WNumber;
    size_t ComAddess;
    int* FlowCounter;
};
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
enum class Opcodes : int {
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
};

class Instruction {
   // friend class Add_command;
public:
    Instruction (Opcodes a,Modifiers b, Mods c, Mods d, int e, int f) : Body(a), OpcodeMod(b),
                                                                        AOperandMod(c),
                                                                        BOperandMod(d),
                                                                        AOperand(e),
                                                                        BOperand(f) {}
    Instruction() {}
    virtual bool Execution (std::vector<Instruction*>&,CircularBuffer&,std::list<Flow>::iterator&){std::cout<<"gde ya..."; return true;}//std::cout<<"gde ya...";}
    virtual bool GetMARSInstruction(std::ifstream &) {};
    virtual bool IsItCorrect() {};
    size_t GettingCode(unsigned i) {
    //    if(Body== Opcodes::DAT&& AOperand==0&& BOperand==0)
      //      return 0;
            std::cout<< static_cast<int>(Body)<< static_cast<int>(OpcodeMod)<< static_cast<char>(AOperandMod)<<AOperand << static_cast<char>(BOperandMod) << BOperand<<"  "<<i<<std::endl ;
        return 0;
    }
    void SetOffset (std::vector<Instruction*>& Core, std::list<Flow>::iterator it, int size,Mods ModAorB,int Operand, int* AorB) {
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
/*    void SetSD(std::vector<Instruction*> Core,std::list<Flow>::iterator it,int size) {
        switch (BOperandMod) {
            case (Mods::Lattice):
                Destination = (*it).Address;
                break;
            case (Mods :: Star):
                Destination = Core[(BOperand+(*it).Address)%size]->AOperand %size;
            case (Mods::Dog):
                Destination = Core[(BOperand + (*it).Address)%size]->BOperand% size;
                break;
            case (Mods::Open):
                Core[(BOperand + (*it).Address)%size]->AOperand--;
            std::cout<<"PROVERYAU ADRES U DATA= "<<Core[(BOperand + (*it).Address)%size]->AOperand<<std::endl;
                Destination = (Core[(BOperand + (*it).Address)%size]->AOperand)% size;
                break;
            case (Mods ::Close):
                Destination = (Core[(BOperand + (*it).Address)%size]->AOperand)% size;
                Core[(AOperand + (*it).Address)%size]->AOperand++;
                break;
            case (Mods::More):
                Destination = (Core[(BOperand + (*it).Address)%size]->BOperand)% size;
                Core[(BOperand + (*it).Address)%size]->BOperand++;
                break;
            case (Mods::Less):
                Core[(BOperand + (*it).Address)%size]->BOperand--;
                Destination = (Core[(BOperand + (*it).Address)%size]->BOperand)% size;
                break;
            case (Mods::Dollar):
            case (Mods :: Not):
            default:
                Destination = (BOperand +(*it).Address) % size;
                break;
        }
        switch (AOperandMod) {
            case (Mods::Lattice):
                Source = (*it).Address;
                break;
            case (Mods::Star):
                Source = Core[(AOperand + (*it).Address)%size]->AOperand% size;
                break;
            case (Mods:: Dog):
                Source = Core[(AOperand+(*it).Address)%size]->BOperand% size;
                break;
            case (Mods::Close):
                Source = Core[(AOperand + (*it).Address) % size]->AOperand % size;
                Core[(AOperand + (*it).Address) % size]->AOperand++;
                break;
            case (Mods::Open):
                Core[(AOperand + (*it).Address)%size]->AOperand--;
                Source = Core[(AOperand + (*it).Address)%size]->AOperand%size;
                break;
            case (Mods::More):
                Source = (Core[(AOperand + (*it).Address)%size]->BOperand)% size;
                Core[(AOperand + (*it).Address)%size]->BOperand++;
                break;
            case (Mods::Less):
                Core[(AOperand + (*it).Address)%size]->BOperand--;
                Source = (Core[(AOperand + (*it).Address)%size]->BOperand)% size;
                break;
            case (Mods::Dollar):
            case (Mods :: Not):
            default:
                Source = (AOperand +(*it).Address) % size;
                break;
        }
        if(Source < 0)
            Source+=size;
        if(Destination<0)
            Destination+=size;
    }*/
    void SetOffsets (std::vector<Instruction*>& Core, std::list<Flow>::iterator it, size_t size) {
        SetOffset(Core,it,size,AOperandMod,AOperand,&AOffset);
        SetOffset(Core,it,size,BOperandMod,BOperand,&BOffset);
    }
    Instruction (const Instruction& in){
        Body = in.Body;
        OpcodeMod=in.OpcodeMod;
        AOperand=in.AOperand;
        BOperand=in.BOperand;
        AOperandMod=in.AOperandMod;
        BOperandMod= in.BOperandMod;
    }
    virtual Instruction* Clone() {
        return new Instruction(*this);
    }
    Instruction& operator = (const Instruction& in) {
        if(this!= &in) {
            /*delete this; // hahahahahaha kept your waiting huh
            if (in.Body == Opcodes::ADD)
            Instruction* tmp = new Add_command;
            *tmp = in;*/
            Body = in.Body;
            AOperandMod = in.AOperandMod;
            BOperandMod = in.BOperandMod;
            OpcodeMod = in.OpcodeMod;
            AOperand = in.AOperand;
            BOperand = in.BOperand;
        }
        return *this;
    }
    static bool IsAmodAllowed (char c) {
        const char allowed [8] = {'@','*','$','#','{','}','>','<'};
        for(size_t i = 0; i < 8; i++)
            if (c==allowed[i])
                return true;
        return false;
    }
    static bool IsBmodAllowed (char c) {
        const char allowed [8] = {'*','@','$','#','<','>','{','}'};
        for(size_t i = 0; i < 8; i++)
            if (c==allowed[i])
                return true;
        return false;
    }
    Opcodes Body;
    Modifiers OpcodeMod;
    Mods AOperandMod;
    Mods BOperandMod;
    int AOperand;
    int BOperand;
protected:
    int Source;
    int Destination;
    int AOffset;
    int BOffset;
};


#endif //CORE_WAR_INSTRUCTIONS_HPP
