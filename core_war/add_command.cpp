#include "factory.hpp"
class Add_command: public Instruction {
public:
    Add_command() {
        Body = Opcodes ::ADD;
        OpcodeMod = Modifiers::AB;
        AOperandMod = Mods::Lattice;
        BOperandMod = Mods::Lattice;
        AOperand = 0;
        BOperand = 0;
    }
    explicit Add_command(Modifiers x){Body= Opcodes ::ADD,OpcodeMod=x;}
    Add_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
        Body = a;
        OpcodeMod = b;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = e;
        BOperand =f;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        SetOffsets(Core,it,size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                Core[BOffset]->AOperand = (Core[AOffset]->AOperand+Core[BOffset]->AOperand)%size;
                break;
            case (Modifiers::B) :
                Core[BOffset]->BOperand = (Core[AOffset]->BOperand+Core[BOffset]->BOperand)%size;
                break;
            case (Modifiers::AB):
                Core[BOffset]->BOperand = (Core[BOffset]->BOperand+Core[AOffset]->AOperand)%size;
                break;
            case (Modifiers::BA):
                Core[BOffset]->AOperand = (Core[BOffset]->AOperand+ Core[AOffset]->BOperand)%size;
                break;
            case (Modifiers ::I):
            case (Modifiers::F):
                Core[BOffset]->AOperand = (Core[AOffset]->AOperand+Core[BOffset]->AOperand)%size;
                Core[BOffset]->BOperand = (Core[AOffset]->BOperand+Core[BOffset]->BOperand)%size;
                break;
            case (Modifiers::X):
            case (Modifiers::Not):
            default:
                Core[BOffset]->BOperand = (Core[AOffset]->AOperand+Core[BOffset]->BOperand)%size;
                Core[BOffset]->AOperand = (Core[AOffset]->BOperand+Core[BOffset]->AOperand)%size;
                break;

        }
        (*it).Address = ((*it).Address+1)%size;
        return true;
    }
    Add_command* Clone() override {
        return new Add_command(*this);
    }
};
Instruction* ac() {
    return new Add_command;
}
Instruction* addab() {return new Add_command(Modifiers::AB);}
Instruction* addba() {return new Add_command(Modifiers::BA);}
Instruction* addta() {return new Add_command(Modifiers::A);}
Instruction* addtb() {return new Add_command(Modifiers::B);}
Instruction* addtf() {return new Add_command(Modifiers::F);}
Instruction* addx() {return new Add_command(Modifiers::X);}
Instruction* addi() {return new Add_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("ADD.AB",&addab);
    bool b = Factory::get_instance()->regist3r("ADD.BA",&addba);
    bool c = Factory::get_instance()->regist3r("ADD.A",&addta);
    bool d = Factory::get_instance()->regist3r("ADD.B",&addtb);
    bool f = Factory::get_instance()->regist3r("ADD.F",&addtf);
    bool e = Factory::get_instance()->regist3r("ADD.X",&addx);
    bool g = Factory::get_instance()->regist3r("ADD.I",&addi);
}
