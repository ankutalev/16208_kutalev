
#include "factory.hpp"
class Nop_command : public Instruction {
public:
    Nop_command() {}
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        std::cout<< "<^-^>/ meow!!"<<std::endl;
        (*it).Address++;
        return true;
    }
    Nop_command* Clone() override {
        return new Nop_command(*this);
    }
};
Instruction* Nopc () {
    return new Nop_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::NOP,Nopc);
}