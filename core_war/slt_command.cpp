
#include "factory.hpp"
class Slt_command : public Instruction {
public:
    explicit Slt_command(Modifiers x) { Body = Opcodes ::SLT, OpcodeMod = x;}
    Slt_command() {}
    Slt_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
        Body = a;
        OpcodeMod = b;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = e;
        BOperand =f;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        SetOffsets(Core,it,size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                (Core[AOffset]->AOperand<Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::B) :
                (Core[AOffset]->BOperand<Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::AB):
                (Core[AOffset]->AOperand<Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::BA):
                (Core[AOffset]->BOperand<Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::F):
            case (Modifiers::I):
                (Core[AOffset]->AOperand<Core[BOffset]->AOperand || Core[AOffset]->BOperand<Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::X):
                (Core[AOffset]->AOperand<Core[BOffset]->BOperand || Core[AOffset]->BOperand<Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
        }
        return true;
    }
    Slt_command* Clone() override {
        return new Slt_command(*this);
    }
};
Instruction* Sltc () {
    return new Slt_command;
}
Instruction* sltab() {return new Slt_command(Modifiers::AB);}
Instruction* sltba() {return new Slt_command(Modifiers::BA);}
Instruction* sltta() {return new Slt_command(Modifiers::A);}
Instruction* slttb() {return new Slt_command(Modifiers::B);}
Instruction* slttf() {return new Slt_command(Modifiers::F);}
Instruction* sltx() {return new Slt_command(Modifiers::X);}
Instruction* slti() {return new Slt_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("SLT.AB",&sltab);
    bool b = Factory::get_instance()->regist3r("SLT.BA",&sltba);
    bool c = Factory::get_instance()->regist3r("SLT.A",&sltta);
    bool d = Factory::get_instance()->regist3r("SLT.B",&slttb);
    bool f = Factory::get_instance()->regist3r("SLT.F",&slttf);
    bool e = Factory::get_instance()->regist3r("SLT.X",&sltx);
    bool g = Factory::get_instance()->regist3r("SLT.I",&slti);
}