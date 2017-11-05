#include "factory.hpp"
class Jmz_command: public Instruction {
public:
    Jmz_command() {
        Body = Opcodes ::JMZ;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Jmz_command (Mods c,int a,Mods d, int b) {
        Body = Opcodes ::JMZ;
        OpcodeMod = Modifiers::A;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = a;
        BOperand = b;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        if(!Destination)
            (*it).Address = Source;
        return true;
    }
    Jmz_command* Clone() override {
        return new Jmz_command(*this);
    }
};
Instruction* jmz () {
    return new Jmz_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::JMZ,jmz);
}