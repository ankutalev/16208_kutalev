#include "factory.hpp"
class Mul_command: public Instruction {
public:
    explicit Mul_command(Modifiers x){OpcodeMod=x;}
    void Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, CircularBuffer::Iterator& it) override {
        size_t size = Core.size();
        SetOffsets(Core,it,size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                Core[BOffset]->AOperand = (Core[AOffset]->AOperand*Core[BOffset]->AOperand)%size;
                break;
            case (Modifiers::B) :
                Core[BOffset]->BOperand = (Core[AOffset]->BOperand*Core[BOffset]->BOperand)%size;
                break;
            case (Modifiers::AB):
                Core[BOffset]->BOperand = (Core[BOffset]->BOperand*Core[AOffset]->AOperand)%size;
                break;
            case (Modifiers::BA):
                Core[BOffset]->AOperand = (Core[BOffset]->AOperand* Core[AOffset]->BOperand)%size;
                break;
            case (Modifiers ::I):
            case (Modifiers::Not):
            case (Modifiers::F):
                Core[BOffset]->AOperand = (Core[AOffset]->AOperand*Core[BOffset]->AOperand)%size;
                Core[BOffset]->BOperand = (Core[AOffset]->BOperand*Core[BOffset]->BOperand)%size;
                break;
            case (Modifiers::X):
                Core[BOffset]->BOperand = (Core[AOffset]->AOperand*Core[BOffset]->BOperand)%size;
                Core[BOffset]->AOperand = (Core[AOffset]->BOperand*Core[BOffset]->AOperand)%size;
                break;

        }
        (*it).Address = ((*it).Address+1)%size;
    }
    Mul_command* Clone() override {
        return new Mul_command(*this);
    }
};
Instruction* Mulab() {return new Mul_command(Modifiers::AB);}
Instruction* Mulba() {return new Mul_command(Modifiers::BA);}
Instruction* Multa() {return new Mul_command(Modifiers::A);}
Instruction* Multb() {return new Mul_command(Modifiers::B);}
Instruction* Multf() {return new Mul_command(Modifiers::F);}
Instruction* Mulx() {return new Mul_command(Modifiers::X);}
Instruction* Muli() {return new Mul_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("MUL.AB",&Mulab);
    bool b = Factory::get_instance()->regist3r("MUL.BA",&Mulba);
    bool c = Factory::get_instance()->regist3r("MUL.A",&Multa);
    bool d = Factory::get_instance()->regist3r("MUL.B",&Multb);
    bool f = Factory::get_instance()->regist3r("MUL.F",&Multf);
    bool e = Factory::get_instance()->regist3r("MUL.X",&Mulx);
    bool g = Factory::get_instance()->regist3r("MUL.I",&Muli);
}
