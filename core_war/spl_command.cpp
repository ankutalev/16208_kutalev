#include "factory.hpp"
#include "loader.h"

class Spl_command: public Instruction {
public:
    Spl_command() {
        Body = Opcodes ::SPL;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Spl_command (Mods c,int a) {
        Body = Opcodes ::SPL;
        OpcodeMod = Modifiers::A;
        AOperandMod = c;
        BOperandMod = Mods::Not;
        AOperand = a;
        BOperand = 0;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        if( (*(*it).FlowCounter) < Queue.FlowCounter ) {
            Flow tmp = (*it);
            tmp.Address = Core[Source]->AOperand;
            Queue.InsertPrev(it, tmp);
            return true;
        }
    }
    Spl_command* Clone() override {
        return new Spl_command(*this);
    }
};
Instruction* sp () {
    return new Spl_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::SPL,sp);
}