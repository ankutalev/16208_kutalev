#include "factory.hpp"
class Add_command: public Instruction {
public:
    Add_command() {
        Body = Opcodes ::ADD;
        OpcodeMod = Modifiers::AB;
        AOperandMod = Mods::Lattice;
        BOperandMod = Mods::Lattice;
        AOperand = 0;
        BOperand = 0;
    }
    Add_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
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
        Core[Destination]->BOperand+= Source;
        (*it).Address = ((*it).Address+1)%size;
        return true;
    }
    Add_command* Clone() override {
        return new Add_command(*this);
    }
};
Instruction* ac() {
    return new Add_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::ADD, ac);
}