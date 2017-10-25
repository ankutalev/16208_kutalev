//
// Created by ulyssess on 24.10.17.
//

#ifndef CORE_WAR_INSTRUCTIONS_HPP
#define CORE_WAR_INSTRUCTIONS_HPP

#include <vector>
#include <iostream>
struct zaglushka {
    int WNumber;
    int ComAddess;
};
enum class Mods :int  { Lattice = 1, Dollar = 2, Dog = 3, Star = 4, Less = 5, More = 6, Open =7, Close =8, Not = 0};
enum class Modifiers :int   { A = 1, B =2, AB=3, BA=4, F=5, X=6, I=6, Not=0};
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
    CMP = 11,
    SEQ = 12,
    SNE = 13,
    SLT = 14,
    SPL = 15,
    NOP = 16,
    ORG
};

class Instruction {
public:
    Instruction (Opcodes a,Modifiers b, Mods c, Mods d, int e, int f) : Body(a), OpcodeMod(b),
                                                                        AOperandMod(c),
                                                                        BOperandMod(d),
                                                                        AOperand(e),
                                                                        BOperand(f) {}
    Instruction() {}
    virtual bool Execution(std::vector<Instruction*>&  core,size_t in) { std::cout<< "gde ya...";}
    virtual bool GetMARSInstruction(std::ifstream &) {};
    virtual bool IsItCorrect(std::string &) {};
    size_t GettingCode(unsigned CoreSize) {
        size_t Code = (BOperand+CoreSize)%CoreSize + (CoreSize+AOperand)%CoreSize*10000 +
                      static_cast<int>(BOperandMod)*100000000 + static_cast<int>(AOperandMod)*1000000000+
                      static_cast<int>(OpcodeMod)*10000000000 + static_cast<int>(Body)*100000000000;
        return Code;
    }
    Instruction& operator = (const Instruction& in) {
        if(this!= &in) {
            Body = in.Body;
            AOperandMod = in.AOperandMod;
            BOperandMod = in.BOperandMod;
            OpcodeMod = in.OpcodeMod;
            AOperand = in.AOperand;
            BOperand = in.BOperand;
        }
        return *this;
    }

protected:
    Opcodes Body;
    Modifiers OpcodeMod;
    Mods AOperandMod;
    Mods BOperandMod;
    int AOperand;
    int BOperand;
//    size_t CoreLocation;
};
class Mov_command : public Instruction {
public:
    Mov_command() {}
    Mov_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
            Body = a;
            OpcodeMod = b;
            AOperandMod = c;
            BOperandMod = d;
            AOperand = e;
            BOperand =f;
        }
    bool Execution (std::vector<Instruction*>& Core, size_t Address) override {
         size_t size = Core.size();
    size_t Destination = BOperand;
    size_t Source = AOperand;
   /* switch (BOperandMod) { //to do for other operand mods (not only # and $)
        case (Mods::Dollar):
            Destination = (Destination +Address)%size;
        case (Mods::Lattice):
    }*/
    if (BOperandMod==Mods::Dollar)
        Destination = (Destination + Address)%size;
    if(AOperandMod==Mods::Dollar)
        Source = (Source+Address)%size;
         Core[Destination]=Core[Source];
         return true;
    }
private:
    int t;
};

class Dat_command: public Instruction {
public:
    bool Execution (std::vector<Instruction*>&, size_t) override;
};

#endif //CORE_WAR_INSTRUCTIONS_HPP
