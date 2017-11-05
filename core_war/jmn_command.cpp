#include "factory.hpp"
class Jmn_command: public Instruction {
public:
    Jmn_command() {
        Body = Opcodes ::JMN;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Jmn_command (Mods c,int a,Mods d, int b) {
        Body = Opcodes ::JMN;
        OpcodeMod = Modifiers::A;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = a;
        BOperand = b;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        if(Destination)
            (*it).Address = Source;
        return true;
    }
    Jmn_command* Clone() override {
        return new Jmn_command(*this);
    }
};
Instruction* Jmnc () {
    return new Jmn_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::JMN,Jmnc);
}