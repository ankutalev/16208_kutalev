
#include "factory.hpp"
class Nop_command : public Instruction {
public:
    explicit Nop_command (Modifiers x) { Fields.OpcodeMod = x; Name = "NOP";  }
    Nop_command() = default;
    void Execution(ExecutionContext& Executor) override {
        std::cout<<Executor.getCurrentWarriorName()<< " have a nice cat! <^-^>/ meow!!"<<std::endl;
    }
    Nop_command* Clone() override {
        return new Nop_command(*this);
    }
};

namespace {
    Instruction* nopab() {return new Nop_command(Modifiers::AB);}
    Instruction* nopba() {return new Nop_command(Modifiers::BA);}
    Instruction* nopta() {return new Nop_command(Modifiers::A);}
    Instruction* noptb() {return new Nop_command(Modifiers::B);}
    Instruction* noptf() {return new Nop_command(Modifiers::F);}
    Instruction* nopx() {return new Nop_command(Modifiers::X);}
    Instruction* nopi() {return new Nop_command(Modifiers::I);}
    bool a = Factory::get_instance()->regist3r("NOP.AB",&nopab);
    bool b = Factory::get_instance()->regist3r("NOP.BA",&nopba);
    bool c = Factory::get_instance()->regist3r("NOP.A",&nopta);
    bool d = Factory::get_instance()->regist3r("NOP.B",&noptb);
    bool f = Factory::get_instance()->regist3r("NOP.F",&noptf);
    bool e = Factory::get_instance()->regist3r("NOP.X",&nopx);
    bool g = Factory::get_instance()->regist3r("NOP.I",&nopi);
bool w = Factory::get_instance()->nameRegister("NOP","NOP");
}