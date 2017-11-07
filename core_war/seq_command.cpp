
#include "factory.hpp"
class Seq_command : public Instruction {
public:
    Seq_command() {}
    Seq_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
        Body = a;
        OpcodeMod = b;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = e;
        BOperand =f;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        size_t size = Core.size();
        SetSD(Core,it,size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                (Core[Source]->AOperand==Core[Destination]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::B) :
                (Core[Source]->BOperand==Core[Destination]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::AB):
                (Core[Source]->AOperand==Core[Destination]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::BA):
                (Core[Source]->BOperand==Core[Destination]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::F):
                (Core[Source]->AOperand==Core[Destination]->AOperand && Core[Source]->BOperand==Core[Destination]->BOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers::X):
                (Core[Source]->AOperand==Core[Destination]->BOperand && Core[Source]->BOperand==Core[Destination]->AOperand) ? (*it).Address=((*it).Address+2)%size : (*it).Address=((*it).Address+1)%size;
                break;
            case (Modifiers ::I):
                (Core[Source]==Core[Destination]) ? ((*it).Address+2)%size : ((*it).Address+1)%size;
                break;
        }
        return true;
    }
    Seq_command* Clone() override {
        return new Seq_command(*this);
    }
};
Instruction* seqc () {
    return new Seq_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::SEQ,seqc);
}