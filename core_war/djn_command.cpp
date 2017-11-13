#include "factory.hpp"
class Djn_command: public Instruction {
public:
    explicit Djn_command(Modifiers x){Body= Opcodes ::DJN,OpcodeMod=x;}
    Djn_command() {
        Body = Opcodes ::DJN;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Djn_command (Mods c,int a,Mods d, int b) {
        Body = Opcodes ::DJN;
        OpcodeMod = Modifiers::A;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = a;
        BOperand = b;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        SetOffsets(Core,it,size);
        if (AOperandMod == Mods::Lattice)
            AOffset = AOperand;
        if (BOperandMod == Mods::Lattice)
            BOffset = BOperand;
        switch (OpcodeMod) {
            case (Modifiers::A) :
            case (Modifiers::BA):
                Core[BOffset]->AOperand--;
                (Core[BOffset]->AOperand) ? (*it).Address = AOffset : ((*it).Address++)%size;
                break;
            case (Modifiers::B) :
            case (Modifiers::AB):
                Core[BOffset]->BOperand--;
                (Core[BOffset]->BOperand) ? (*it).Address = AOffset : ((*it).Address++)%size;
                break;
            case (Modifiers ::I):
            case (Modifiers::F):
            case (Modifiers::X):
                Core[BOffset]->AOperand--;
                Core[BOffset]->BOperand--;
                (Core[BOffset]->BOperand|| Core[BOffset]->AOperand) ? (*it).Address = AOffset : ((*it).Address++)%size;
                break;

        }
        (*it).Address%=size;
        if ((*it).Address < 0)
            (*it).Address+=size;
        return true;
    }
    Djn_command* Clone() override {
        return new Djn_command(*this);
    }
};
Instruction* Djnab() {return new Djn_command(Modifiers::AB);}
Instruction* Djnba() {return new Djn_command(Modifiers::BA);}
Instruction* Djnta() {return new Djn_command(Modifiers::A);}
Instruction* Djntb() {return new Djn_command(Modifiers::B);}
Instruction* Djntf() {return new Djn_command(Modifiers::F);}
Instruction* Djnx() {return new Djn_command(Modifiers::X);}
Instruction* Djni() {return new Djn_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("DJN.AB",&Djnab);
    bool b = Factory::get_instance()->regist3r("DJN.BA",&Djnba);
    bool c = Factory::get_instance()->regist3r("DJN.A",&Djnta);
    bool d = Factory::get_instance()->regist3r("DJN.B",&Djntb);
    bool f = Factory::get_instance()->regist3r("DJN.F",&Djntf);
    bool e = Factory::get_instance()->regist3r("DJN.X",&Djnx);
    bool g = Factory::get_instance()->regist3r("DJN.I",&Djni);
}

