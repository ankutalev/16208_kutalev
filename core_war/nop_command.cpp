
#include "factory.hpp"
class Nop_command : public Instruction {
public:
    explicit Nop_command (Modifiers x) { Body = Opcodes ::NOP; OpcodeMod = x;}
    Nop_command() {}
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        std::cout<< "<^-^>/ meow!!"<<std::endl;
        (*it).Address=((*it).Address+1)%size;
        return true;
    }
    Nop_command* Clone() override {
        return new Nop_command(*this);
    }
};
Instruction* Nopc () {
    return new Nop_command;
}
Instruction* nopab() {return new Nop_command(Modifiers::AB);}
Instruction* nopba() {return new Nop_command(Modifiers::BA);}
Instruction* nopta() {return new Nop_command(Modifiers::A);}
Instruction* noptb() {return new Nop_command(Modifiers::B);}
Instruction* noptf() {return new Nop_command(Modifiers::F);}
Instruction* nopx() {return new Nop_command(Modifiers::X);}
Instruction* nopi() {return new Nop_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("NOP.AB",&nopab);
    bool b = Factory::get_instance()->regist3r("NOP.BA",&nopba);
    bool c = Factory::get_instance()->regist3r("NOP.A",&nopta);
    bool d = Factory::get_instance()->regist3r("NOP.B",&noptb);
    bool f = Factory::get_instance()->regist3r("NOP.F",&noptf);
    bool e = Factory::get_instance()->regist3r("NOP.X",&nopx);
    bool g = Factory::get_instance()->regist3r("NOP.I",&nopi);
}