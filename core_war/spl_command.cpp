#include "factory.hpp"
#include "loader.h"

class Spl_command: public Instruction {
public:
    explicit Spl_command(Modifiers x) { Body = Opcodes ::SPL, OpcodeMod = x;}
    Spl_command() {
        Body = Opcodes ::SPL;
        OpcodeMod = Modifiers::A;
        AOperandMod = Mods::Dollar;
        BOperandMod = Mods::Not;
        AOperand = 0;
        BOperand = 0;
    }
    Spl_command (Mods c,int a) {
        Body = Opcodes ::SPL;
        OpcodeMod = Modifiers::A;
        AOperandMod = c;
        BOperandMod = Mods::Not;
        AOperand = a;
        BOperand = 0;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator& it) override {
        size_t size = Core.size();
        SetOffset(Core,it,size,AOperandMod,AOperand,&AOffset);
        if (AOperandMod == Mods::Lattice)
            AOffset = AOperand;
        if (BOperandMod == Mods::Lattice)
            BOffset = BOperand;
        if( (*(*it).FlowCounter) < Queue.FlowCounter ) {
            Flow tmp = (*it);
            tmp.Address = AOffset%size;
            Queue.InsertPrev(it, tmp);
        }
        else
            std::cout<<"TOO MUCH FLOWS"<<std::endl;
        (*it).Address=((*it).Address+1)%size;
        return true;
    }
    Spl_command* Clone() override {
        return new Spl_command(*this);
    }
};
Instruction* sp () {
    return new Spl_command;
}
Instruction* splab() {return new Spl_command(Modifiers::AB);}
Instruction* splba() {return new Spl_command(Modifiers::BA);}
Instruction* splta() {return new Spl_command(Modifiers::A);}
Instruction* spltb() {return new Spl_command(Modifiers::B);}
Instruction* spltf() {return new Spl_command(Modifiers::F);}
Instruction* splx() {return new Spl_command(Modifiers::X);}
Instruction* spli() {return new Spl_command(Modifiers::I);}

namespace {
    bool a = Factory::get_instance()->regist3r("SPL.AB",&splab);
    bool b = Factory::get_instance()->regist3r("SPL.BA",&splba);
    bool c = Factory::get_instance()->regist3r("SPL.A",&splta);
    bool d = Factory::get_instance()->regist3r("SPL.B",&spltb);
    bool f = Factory::get_instance()->regist3r("SPL.F",&spltf);
    bool e = Factory::get_instance()->regist3r("SPL.X",&splx);
    bool g = Factory::get_instance()->regist3r("SPL.I",&spli);
}