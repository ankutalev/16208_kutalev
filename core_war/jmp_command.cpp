//#include "instructions.hpp"
#include "factory.hpp"
class Jmp_command: public Instruction {
public:
    Jmp_command() {
        Body = Opcodes ::JMP;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Jmp_command (Mods c,int a) {
        Body = Opcodes ::JMP;
        OpcodeMod = Modifiers::A;
        AOperandMod = c;
        BOperandMod = Mods::Not;
        AOperand = a;
        BOperand = 0;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        (*it).Address = Core[Source]->AOperand;
        return true;
    }
    Jmp_command* Clone() override {
        return new Jmp_command(*this);
    }
};
Instruction* jm () {
    return new Jmp_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::JMP,jm);
}