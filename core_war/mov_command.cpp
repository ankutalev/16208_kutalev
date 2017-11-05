
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
        SetSD(Core,it,size);
        (*it).Address=((*it).Address+1)%size;
        delete Core[Destination];
        //Core [Destination] = Factory::get_instance()->create(Core[Source]->Body);
       // *Core[Destination] = *Core[Source];
        Core[Destination] = Core[Source]->Clone();
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