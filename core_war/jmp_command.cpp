//#include "instructions.hpp"
#include "factory.hpp"
class Jmp_command: public Instruction {
public:
    explicit Jmp_command(Modifiers x){Body= Opcodes ::JMP,OpcodeMod=x;}
    Jmp_command() {
        Body = Opcodes ::JMP;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Jmp_command (Mods c,int a) {
        Body = Opcodes ::JMP;
        OpcodeMod = Modifiers::A;
        AOperandMod = c;
        BOperandMod = Mods::Not;
        AOperand = a;
        BOperand = 0;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        int size = Core.size();
        SetSD(Core,it,size);
        if (AOperandMod == Mods::Lattice)
            Source = AOperand;
        (*it).Address = ((*it).Address=Source)%size;
        if ((*it).Address < 0)
            ((*it).Address+=size);
        return true;
    }
    Jmp_command* Clone() override {
        return new Jmp_command(*this);
    }
};
Instruction* jm () {
    return new Jmp_command;
}
Instruction* Jmpab() {return new Jmp_command(Modifiers::AB);}
Instruction* Jmpba() {return new Jmp_command(Modifiers::BA);}
Instruction* Jmpta() {return new Jmp_command(Modifiers::A);}
Instruction* Jmptb() {return new Jmp_command(Modifiers::B);}
Instruction* Jmptf() {return new Jmp_command(Modifiers::F);}
Instruction* Jmpx() {return new Jmp_command(Modifiers::X);}
Instruction* Jmpi() {return new Jmp_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("JMP.AB",&Jmpab);
    bool b = Factory::get_instance()->regist3r("JMP.BA",&Jmpba);
    bool c = Factory::get_instance()->regist3r("JMP.A",&Jmpta);
    bool d = Factory::get_instance()->regist3r("JMP.B",&Jmptb);
    bool f = Factory::get_instance()->regist3r("JMP.F",&Jmptf);
    bool e = Factory::get_instance()->regist3r("JMP.X",&Jmpx);
    bool g = Factory::get_instance()->regist3r("JMP.I",&Jmpi);
}