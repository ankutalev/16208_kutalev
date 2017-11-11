#include "factory.hpp"
class Div_command: public Instruction {
public:
    explicit Div_command(Modifiers x){Body= Opcodes ::DIV,OpcodeMod=x;}
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
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        if (!Core[Source]->AOperand&& (OpcodeMod!= Modifiers::BA) && (OpcodeMod!=Modifiers::B)) {
            Queue.DeleteCurrent(it);
            return true;
        }
        if (!Core[Source]->BOperand&& (OpcodeMod!= Modifiers::AB) && (OpcodeMod!=Modifiers::A)) {
            Queue.DeleteCurrent(it);
            return true;
        }

        switch (OpcodeMod) {
            case (Modifiers::A) :
                Core[Destination]->AOperand /= Core[Source]->AOperand;
                break;
            case (Modifiers::AB):
                Core[Destination]->BOperand /= Core[Source]->AOperand;
                break;
            case (Modifiers::B) :
                Core[Destination]->BOperand /= Core[Source]->BOperand;
                break;
            case (Modifiers::BA):
                Core[Destination]->AOperand /= Core[Source]->BOperand;
                break;
            case (Modifiers ::I):
            case (Modifiers::F):
                Core[Destination]->AOperand /= Core[Source]->AOperand;
                Core[Destination]->BOperand /= Core[Source]->BOperand;
                break;
            case (Modifiers::X):
                Core[Destination]->BOperand /= Core[Source]->AOperand;
                Core[Destination]->AOperand /= Core[Source]->BOperand;
                break;

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
Instruction* divab() {return new Div_command(Modifiers::AB);}
Instruction* divba() {return new Div_command(Modifiers::BA);}
Instruction* divta() {return new Div_command(Modifiers::A);}
Instruction* divtb() {return new Div_command(Modifiers::B);}
Instruction* divtf() {return new Div_command(Modifiers::F);}
Instruction* divx() {return new Div_command(Modifiers::X);}
Instruction* divi() {return new Div_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("DIV.AB",&divab);
    bool b = Factory::get_instance()->regist3r("DIV.BA",&divba);
    bool c = Factory::get_instance()->regist3r("DIV.A",&divta);
    bool d = Factory::get_instance()->regist3r("DIV.B",&divtb);
    bool f = Factory::get_instance()->regist3r("DIV.F",&divtf);
    bool e = Factory::get_instance()->regist3r("DIV.X",&divx);
    bool g = Factory::get_instance()->regist3r("DIV.I",&divi);
}
