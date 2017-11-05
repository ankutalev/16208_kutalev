#include "factory.hpp"
class Div_command: public Instruction {
public:
    Div_command() {
        Body = Opcodes ::DIV;
        OpcodeMod = Modifiers::AB;
        AOperandMod = Mods::Lattice;
        BOperandMod = Mods::Lattice;
        AOperand = 0;
        BOperand = 0;
    }
    Div_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
        Body = a;
        OpcodeMod = b;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = e;
        BOperand =f;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        if (Source)
            Core[Destination]->BOperand/= Source;
        else {
            Queue.DeleteCurrent(it);
            return true;
        }
        (*it).Address = ((*it).Address+1)%size;
        return true;
    }
    Div_command* Clone() override {
        return new Div_command(*this);
    }
};
Instruction* Divc() {
    return new Div_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::DIV, Divc);
}