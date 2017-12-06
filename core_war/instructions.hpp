//
//

#ifndef CORE_WAR_INSTRUCTIONS_HPP
#define CORE_WAR_INSTRUCTIONS_HPP
class Instruction;
struct Data;
enum class Mods:char;
enum class Modifiers;
#include <vector>
#include <iostream>
#include "ExecutionContext.hpp"

enum class Mods : char {
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
enum class Modifiers { A = 1, B =2, AB=3, BA=4, F=5, X=6, I=7, Not=0};

struct Data {
    Modifiers OpcodeMod = Modifiers::F;
    Mods AOperandMod = Mods:: Dollar;
    Mods BOperandMod = Mods::Dollar;
    int AOperand = 0;
    int BOperand = 0;
    int AOffset = 0;
    int BOffset = 0;
};

class Instruction {
public:
    Instruction(){ Fields.OpcodeMod=Modifiers::Not;}


    virtual void Execution (ExecutionContext& Executor) = 0;



    size_t GettingCode(unsigned i) {
        if(Fields.OpcodeMod==Modifiers::F&& !Fields.AOperand&&!Fields.BOperand)
            return 0;
            std::cout<< static_cast<int>(Fields.OpcodeMod)<< static_cast<char>(Fields.AOperandMod)<<Fields.AOperand << static_cast<char>(Fields.BOperandMod) << Fields.BOperand<<"  "<<i<<std::endl ;
        return 0;
    }
    Instruction (const Instruction& in) = default;



    virtual Instruction* Clone() = 0;



    static bool IsModAllowed (char c) {
        const char allowed [8] = {'@','*','$','#','{','}','>','<'};
        for (char i : allowed)
            if (c== i)
                return true;
        return false;
    }



    Data& GetData() { return Fields;}


    virtual ~Instruction() = default;

protected:
    std::string Name;
    Data Fields;
};


#endif //CORE_WAR_INSTRUCTIONS_HPP
