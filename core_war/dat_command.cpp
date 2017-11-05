#include "factory.hpp"
class Dat_command: public Instruction {
public:
    Dat_command() {
        Body = Opcodes ::DAT;
        OpcodeMod = Modifiers::AB;
        AOperandMod = Mods::Lattice;
        BOperandMod = Mods::Lattice;
        AOperand = 0;
        BOperand = 0;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
           Queue.DeleteCurrent(it);
        return true;
    }
    bool IsItCorrect (std::string &) override {
        std::cout<<"lafleur";
        return true;
    }
    Dat_command* Clone() override {
        return new Dat_command(*this);
    }
};
Instruction* dc () {
    return new Dat_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::DAT,dc);
}