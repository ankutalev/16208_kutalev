
#include "factory.hpp"
#include <iostream>
class Sne_command : public Instruction {
public:
    explicit Sne_command(Modifiers x) { OpcodeMod = x;}
    void Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, CircularBuffer::Iterator& it) override {
        size_t size = Core.size();
        SetOffsets(Core,it,size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                (Core[AOffset]->AOperand!=Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::B) :
                (Core[AOffset]->BOperand!=Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::AB):
                (Core[AOffset]->AOperand!=Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::BA):
                (Core[AOffset]->BOperand!=Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::F):
                (Core[AOffset]->AOperand!=Core[BOffset]->AOperand || Core[AOffset]->BOperand!=Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::X):
                (Core[AOffset]->AOperand!=Core[BOffset]->BOperand || Core[AOffset]->BOperand!=Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers ::Not):
            case (Modifiers ::I):
                 (Core[AOffset]==Core[BOffset]) ? (*it).Address=((*it).Address+1)%size : (*it).Address=((*it).Address+2)%size;
                break;
        }
    }
    Sne_command* Clone() override {
        return new Sne_command(*this);
    }
};
Instruction* sneab() {return new Sne_command(Modifiers::AB);}
Instruction* sneba() {return new Sne_command(Modifiers::BA);}
Instruction* sneta() {return new Sne_command(Modifiers::A);}
Instruction* snetb() {return new Sne_command(Modifiers::B);}
Instruction* snetf() {return new Sne_command(Modifiers::F);}
Instruction* snex() {return new Sne_command(Modifiers::X);}
Instruction* snei() {return new Sne_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("SNE.AB",&sneab);
    bool b = Factory::get_instance()->regist3r("SNE.BA",&sneba);
    bool c = Factory::get_instance()->regist3r("SNE.A",&sneta);
    bool d = Factory::get_instance()->regist3r("SNE.B",&snetb);
    bool f = Factory::get_instance()->regist3r("SNE.F",&snetf);
    bool e = Factory::get_instance()->regist3r("SNE.X",&snex);
    bool g = Factory::get_instance()->regist3r("SNE.I",&snei);
}