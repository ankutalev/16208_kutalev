
#include "factory.hpp"
class Mov_command : public Instruction {
public:
    Mov_command() {Body = Opcodes:: MOV;}
    Mov_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
        Body = a;
        OpcodeMod = b;
        AOperandMod = c;
        BOperandMod = d;
        AOperand = e;
        BOperand =f;
    }
    bool Execution (std::vector<Instruction*>& Core,CircularBuffer& Queue, std::list<Flow>::iterator it) override {
        size_t size = Core.size();
        SetSD(Core, it, size);
        switch (OpcodeMod) {
            case (Modifiers::A) :
                Core[Destination]->AOperand = Core[Source]->AOperand;
                break;
            case (Modifiers::B) :
                Core[Destination]->BOperand = Core[Source]->BOperand;
                break;
            case (Modifiers::AB):
                Core[Destination]->BOperand=Core[Source]->AOperand;
                break;
            case (Modifiers ::BA):
                Core[Destination]->AOperand=Core[Source]->BOperand;
                break;
            case (Modifiers ::F):
                Core[Destination]->AOperand=Core[Source]->AOperand;
                Core[Destination]->BOperand=Core[Source]->BOperand;
                break;
            case(Modifiers::X):
                Core[Destination]->BOperand=Core[Source]->AOperand;
                Core[Destination]->AOperand=Core[Source]->BOperand;
                break;
            case (Modifiers ::Not):
            case (Modifiers::I):
            std::cout<<"bil tuta"<<std::endl;
            std::cout<<Source<< " "<<Destination<<std::endl;
                delete Core[Destination];
                Core[Destination] = Core[Source]->Clone();
            std::cout<<"bil zdesya";
            break;
        }
        (*it).Address = ((*it).Address + 1) % size;
        return true;
    }

    Mov_command* Clone() override {
        return new Mov_command(*this);
    }
};
Instruction* mc () {
    return new Mov_command;
}
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::MOV,mc);
}