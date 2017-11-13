#include "factory.hpp"
class Jmz_command: public Instruction {
public:
    explicit Jmz_command(Modifiers x){Body= Opcodes ::JMZ,OpcodeMod=x;}
    Jmz_command() {
        Body = Opcodes ::JMZ;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Jmz_command (Mods c,int a,Mods d, int b) {
        Body = Opcodes ::JMZ;
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
                (!Core[BOffset]->AOperand) ? (*it).Address = (AOffset % size) : ((*it).Address+1)%size;
                break;
            case (Modifiers::Not):
            case (Modifiers::B) :
            case (Modifiers::AB):
                (!Core[BOffset]->BOperand) ? (*it).Address = (AOffset % size) : ((*it).Address+1)%size;
                break;
            case (Modifiers ::I):
            case (Modifiers::F):
            case (Modifiers::X):
                (!Core[BOffset]->AOperand&&!Core[BOffset]->BOperand) ? (*it).Address = (AOffset % size) : ((*it).Address+1)%size;
                break;

        }
        (*it).Address%=size;
        if ((*it).Address < 0)
            (*it).Address+=size;
        return true;
    }
    Jmz_command* Clone() override {
        return new Jmz_command(*this);
    }
};
Instruction* Jmzab() {return new Jmz_command(Modifiers::AB);}
Instruction* Jmzba() {return new Jmz_command(Modifiers::BA);}
Instruction* Jmzta() {return new Jmz_command(Modifiers::A);}
Instruction* Jmztb() {return new Jmz_command(Modifiers::B);}
Instruction* Jmztf() {return new Jmz_command(Modifiers::F);}
Instruction* Jmzx() {return new Jmz_command(Modifiers::X);}
Instruction* Jmzi() {return new Jmz_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("JMZ.AB",&Jmzab);
    bool b = Factory::get_instance()->regist3r("JMZ.BA",&Jmzba);
    bool c = Factory::get_instance()->regist3r("JMZ.A",&Jmzta);
    bool d = Factory::get_instance()->regist3r("JMZ.B",&Jmztb);
    bool f = Factory::get_instance()->regist3r("JMZ.F",&Jmztf);
    bool e = Factory::get_instance()->regist3r("JMZ.X",&Jmzx);
    bool g = Factory::get_instance()->regist3r("JMZ.I",&Jmzi);
}