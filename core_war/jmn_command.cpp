#include "factory.hpp"
class Jmn_command: public Instruction {
public:
    explicit Jmn_command(Modifiers x){Body= Opcodes ::JMN,OpcodeMod=x;}
    Jmn_command() {
        Body = Opcodes ::JMN;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Jmn_command (Mods c,int a,Mods d, int b) {
        Body = Opcodes ::JMN;
        OpcodeMod = Modifiers::A;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = a;
        BOperand = b;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        if (AOperandMod == Mods::Lattice)
            Source = AOperand;
        switch (OpcodeMod) {
            case (Modifiers::A) :
            case (Modifiers::BA):
                (Core[Destination]->BOperand) ? ((*it).Address = Source) % size : ((*it).Address+1)%size;
                break;
            case (Modifiers::B) :
            case (Modifiers::AB):
                (Core[Destination]->AOperand) ? ((*it).Address = Source) % size : ((*it).Address+1)%size;
                break;
            case (Modifiers ::I):
            case (Modifiers::F):
            case (Modifiers::X):
                (Core[Destination]->AOperand||Core[Destination]->BOperand) ? ((*it).Address = Source) % size : ((*it).Address+1)%size;
                break;

        }
        if ((*it).Address < 0) 
            (*it).Address+=size;
        return true;
    }
    Jmn_command* Clone() override {
        return new Jmn_command(*this);
    }
};

Instruction* Jmnab() {return new Jmn_command(Modifiers::AB);}
Instruction* Jmnba() {return new Jmn_command(Modifiers::BA);}
Instruction* Jmnta() {return new Jmn_command(Modifiers::A);}
Instruction* Jmntb() {return new Jmn_command(Modifiers::B);}
Instruction* Jmntf() {return new Jmn_command(Modifiers::F);}
Instruction* Jmnx() {return new Jmn_command(Modifiers::X);}
Instruction* Jmni() {return new Jmn_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("JMN.AB",&Jmnab);
    bool b = Factory::get_instance()->regist3r("JMN.BA",&Jmnba);
    bool c = Factory::get_instance()->regist3r("JMN.A",&Jmnta);
    bool d = Factory::get_instance()->regist3r("JMN.B",&Jmntb);
    bool f = Factory::get_instance()->regist3r("JMN.F",&Jmntf);
    bool e = Factory::get_instance()->regist3r("JMN.X",&Jmnx);
    bool g = Factory::get_instance()->regist3r("JMN.I",&Jmni);
}