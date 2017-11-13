
#include "factory.hpp"
class Mov_command : public Instruction {
public:
    Mov_command() {}

    explicit Mov_command(Modifiers x){Body= Opcodes ::MOV,OpcodeMod=x;}
    Mov_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
        Body = a;
        OpcodeMod = b;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = e;
        BOperand =f;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        //SetSD(Core, it, size);

        SetOffsets(Core,it,size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                Core[BOffset]->AOperand = Core[AOffset]->AOperand;
                break;
            case (Modifiers::B) :
                Core[BOffset]->BOperand = Core[AOffset]->BOperand;
                break;
            case (Modifiers::AB):
                Core[BOffset]->BOperand=Core[AOffset]->AOperand;
                break;
            case (Modifiers ::BA):
                Core[BOffset]->AOperand=Core[AOffset]->BOperand;
                break;
            case (Modifiers ::F):
                Core[BOffset]->AOperand=Core[AOffset]->AOperand;
                Core[BOffset]->BOperand=Core[AOffset]->BOperand;
                break;
            case(Modifiers::X):
                Core[BOffset]->BOperand=Core[AOffset]->AOperand;
                Core[BOffset]->AOperand=Core[AOffset]->BOperand;
                break;
            case (Modifiers ::Not):
            case (Modifiers::I):
                if (AOperandMod == Mods::Lattice)
                    AOffset = AOperand;
                if (BOperandMod == Mods::Lattice)
                    BOffset = BOperand;
                if (AOffset!=BOffset){
                    delete Core[BOffset];
                    Core[BOffset] = Core[AOffset]->Clone();
                }
            break;
        }
        (*it).Address = ((*it).Address + 1) % size;
        return true;
    }
    bool IsItCorrect() override {
        std::cout<<"mooooooooooov!"<< static_cast<int>(OpcodeMod);
        return true;
    }
    Mov_command* Clone() override {
        return new Mov_command(*this);
    }
};
Instruction* mc () {
    return new Mov_command;
}
Instruction* movab() {return new Mov_command(Modifiers::AB);}
Instruction* movba() {return new Mov_command(Modifiers::BA);}
Instruction* mova() {return new Mov_command(Modifiers::A);}
Instruction* movb() {return new Mov_command(Modifiers::B);}
Instruction* movf() {return new Mov_command(Modifiers::F);}
Instruction* movx() {return new Mov_command(Modifiers::X);}
Instruction* movi() {return new Mov_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("MOV.AB",&movab);
    bool b = Factory::get_instance()->regist3r("MOV.BA",&movba);
    bool c = Factory::get_instance()->regist3r("MOV.A",&mova);
    bool d = Factory::get_instance()->regist3r("MOV.B",&movb);
    bool f = Factory::get_instance()->regist3r("MOV.F",&movf);
    bool e = Factory::get_instance()->regist3r("MOV.X",&movx);
    bool g = Factory::get_instance()->regist3r("MOV.I",&movi);
}