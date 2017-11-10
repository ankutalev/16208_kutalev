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
    virtual bool Execution (std::vector<Instruction*>&,CircularBuffer&,std::list<Flow>::iterator){}//std::cout<<"gde ya...";}
    virtual bool GetMARSInstruction(std::ifstream &) {};
    virtual bool IsItCorrect() {};
    size_t GettingCode(unsigned CoreSize) {
        std::cout<< static_cast<int>(Body)<< static_cast<int>(OpcodeMod)<< static_cast<char>(AOperandMod)<<AOperand << static_cast<char>(BOperandMod) << BOperand;
        return 0;
    }
    void SetSD(std::vector<Instruction*> Core,std::list<Flow>::iterator it,size_t size) {
        switch (BOperandMod) {
            case (Mods::Lattice):
                Destination = (*it).Address;
                break;
            case (Mods::Dog):
                Destination = Core[(BOperand + (*it).Address)%size]->BOperand;
                break;
            case (Mods::More):
                Destination = Core[(BOperand + (*it).Address)%size]->BOperand+1;
                break;
            case (Mods::Less):
                Destination = Core[(BOperand + (*it).Address)%size+1]->BOperand;
                break;
            case (Mods::Dollar):
            case (Mods :: Not):
            default:
                Destination = (BOperand +(*it).Address);
                break;
        }
        switch (AOperandMod) {
            case (Mods::Lattice):
                Source = (*it).Address;
                break;
            case (Mods::Star):
                Source = Core[(AOperand + (*it).Address)%size]->AOperand;
                break;
            case (Mods::Close):
                Source = Core[(AOperand + (*it).Address)%size]->AOperand+1;
                break;
            case (Mods::Open):
                Source = Core[(AOperand + (*it).Address)%size+1]->AOperand;
                break;
            case (Mods::Dollar):
            case (Mods :: Not):
            default:
                Source = (AOperand +(*it).Address);
                break;
        }
        while(Source<0 || Destination<0) {
            Source+=size;
            Destination+=size;
        }
        Source%=size;
        Destination%=size;
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
        const char allowed [5] = {'*','$','#','{','}'};
        for(size_t i = 0; i < 5; i++)
            if (c==allowed[i])
                return true;
        return false;
    }
    static bool IsBmodAllowed (char c) {
        const char allowed [5] = {'@','$','#','<','>'};
        for(size_t i = 0; i < 5; i++)
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
};


#endif //CORE_WAR_INSTRUCTIONS_HPP
