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
    explicit Dat_command(Modifiers x){Body= Opcodes ::DAT,OpcodeMod=x;}
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        std::cout<<"dsa";
        Queue.DeleteCurrent(it);
        return true;
    }
    Dat_command* Clone() override {
        return new Dat_command(*this);
    }
};
Instruction* dc () {
    return new Dat_command;
}
Instruction* datab() {return new Dat_command(Modifiers::AB);}
Instruction* datba() {return new Dat_command(Modifiers::BA);}
Instruction* data() {return new Dat_command(Modifiers::A);}
Instruction* datb() {return new Dat_command(Modifiers::B);}
Instruction* datf() {return new Dat_command(Modifiers::F);}
Instruction* datx() {return new Dat_command(Modifiers::X);}
Instruction* dati() {return new Dat_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("DAT.AB",&datab);
    bool b = Factory::get_instance()->regist3r("DAT.BA",&datba);
    bool c = Factory::get_instance()->regist3r("DAT.A",&data);
    bool d = Factory::get_instance()->regist3r("DAT.B",&datb);
    bool f = Factory::get_instance()->regist3r("DAT.F",&datf);
    bool e = Factory::get_instance()->regist3r("DAT.X",&datx);
    bool g = Factory::get_instance()->regist3r("DAT.I",&dati);
}   