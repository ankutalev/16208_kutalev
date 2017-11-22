
#include "factory.hpp"
class Seq_command : public Instruction {
public:
    explicit Seq_command(Modifiers x) { OpcodeMod = x;}
    Seq_command() {}
    Seq_command( Modifiers b, Mods c, Mods d, int e, int f) {
        OpcodeMod = b;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = e;
        BOperand =f;
    }
    void Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, CircularBuffer::Iterator& it) override {
        size_t size = Core.size();
       // SetSD(Core,it,size);
        SetOffsets(Core,it,size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                (Core[AOffset]->AOperand==Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::B) :
                (Core[AOffset]->BOperand==Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::AB):
                (Core[AOffset]->AOperand==Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::BA):
                (Core[AOffset]->BOperand==Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;

            case (Modifiers::F):
                (Core[AOffset]->AOperand==Core[BOffset]->AOperand && Core[AOffset]->BOperand==Core[BOffset]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::X):
                (Core[AOffset]->AOperand==Core[BOffset]->BOperand && Core[AOffset]->BOperand==Core[BOffset]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::Not):
            case (Modifiers ::I):
                (Core[AOffset]==Core[BOffset]) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
        }
    }
    Seq_command* Clone() override {
        return new Seq_command(*this);
    }
};
Instruction* seqc () {
    return new Seq_command;
}
Instruction* seqab() {return new Seq_command(Modifiers::AB);}
Instruction* seqba() {return new Seq_command(Modifiers::BA);}
Instruction* seqta() {return new Seq_command(Modifiers::A);}
Instruction* seqtb() {return new Seq_command(Modifiers::B);}
Instruction* seqtf() {return new Seq_command(Modifiers::F);}
Instruction* seqx() {return new Seq_command(Modifiers::X);}
Instruction* seqi() {return new Seq_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("SEQ.AB",&seqab);
    bool b = Factory::get_instance()->regist3r("SEQ.BA",&seqba);
    bool c = Factory::get_instance()->regist3r("SEQ.A",&seqta);
    bool d = Factory::get_instance()->regist3r("SEQ.B",&seqtb);
    bool f = Factory::get_instance()->regist3r("SEQ.F",&seqtf);
    bool e = Factory::get_instance()->regist3r("SEQ.X",&seqx);
    bool g = Factory::get_instance()->regist3r("SEQ.I",&seqi);
}