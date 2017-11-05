#include "factory.hpp"
class Mul_command: public Instruction {
public:
    Mul_command() {
        Body = Opcodes ::MUL;
        OpcodeMod = Modifiers::AB;
        AOperandMod = Mods::Lattice;
        BOperandMod = Mods::Lattice;
        AOperand = 0;
        BOperand = 0;
    }
    Mul_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
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
        Core[Destination]->BOperand*= Source;
        (*it).Address = ((*it).Address+1)%size;
        return true;
    }
    Mul_command* Clone() override {
        return new Mul_command(*this);
    }
};
Instruction* mulc() {
    return new Mul_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::MUL, mulc);
}