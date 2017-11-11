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
    explicit Mul_command(Modifiers x){Body= Opcodes ::MUL,OpcodeMod=x;}
    Mul_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
        Body = a;
        OpcodeMod = b;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = e;
        BOperand =f;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                Core[Destination]->AOperand = (Core[Source]->AOperand*Core[Destination]->AOperand)%size;
                break;
            case (Modifiers::B) :
                Core[Destination]->BOperand = (Core[Source]->BOperand*Core[Destination]->BOperand)%size;
                break;
            case (Modifiers::AB):
                Core[Destination]->BOperand = (Core[Destination]->BOperand*Core[Source]->AOperand)%size;
                break;
            case (Modifiers::BA):
                Core[Destination]->AOperand = (Core[Destination]->AOperand*Core[Source]->BOperand)%size;
                break;
            case (Modifiers ::I):
            case (Modifiers::F):
                Core[Destination]->AOperand = (Core[Source]->AOperand*Core[Destination]->AOperand)%size;
                Core[Destination]->BOperand = (Core[Source]->BOperand*Core[Destination]->BOperand)%size;
                break;
            case (Modifiers::X):
            case (Modifiers::Not):
            default:
                Core[Destination]->BOperand = (Core[Source]->AOperand*Core[Destination]->BOperand)%size;
                Core[Destination]->AOperand = (Core[Source]->BOperand*Core[Destination]->AOperand)%size;
                break;

        }
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
Instruction* mulab() {return new Mul_command(Modifiers::AB);}
Instruction* mulba() {return new Mul_command(Modifiers::BA);}
Instruction* multa() {return new Mul_command(Modifiers::A);}
Instruction* multb() {return new Mul_command(Modifiers::B);}
Instruction* multf() {return new Mul_command(Modifiers::F);}
Instruction* mulx() {return new Mul_command(Modifiers::X);}
Instruction* muli() {return new Mul_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("MUL.AB",&mulab);
    bool b = Factory::get_instance()->regist3r("MUL.BA",&mulba);
    bool c = Factory::get_instance()->regist3r("MUL.A",&multa);
    bool d = Factory::get_instance()->regist3r("MUL.B",&multb);
    bool f = Factory::get_instance()->regist3r("MUL.F",&multf);
    bool e = Factory::get_instance()->regist3r("MUL.X",&mulx);
    bool g = Factory::get_instance()->regist3r("MUL.I",&muli);
}
