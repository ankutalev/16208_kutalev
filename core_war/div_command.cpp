#include "factory.hpp"
class Div_command: public Instruction {
public:
    Div_command() {
        Body = Opcodes ::DIV;
        OpcodeMod = Modifiers::AB;
        AOperandMod = Mods::Lattice;
        BOperandMod = Mods::Lattice;
        AOperand = 0;
        BOperand = 0;
    }
    Div_command(Opcodes a, Modifiers b, Mods c, Mods d, int e, int f) {
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
        if (Source)
            Core[Destination]->BOperand/= Source;
        else {
            Queue.DeleteCurrent(it);
            return true;
        }
        if (!Core[Source]->AOperand&& (OpcodeMod!= Modifiers::BA) && (OpcodeMod!=Modifiers::B)) {
            Queue.DeleteCurrent(it);
            return true;
        }
        if (!Core[Source]->BOperand&& (OpcodeMod!= Modifiers::AB) && (OpcodeMod!=Modifiers::A)) {
            Queue.DeleteCurrent(it);
            return true;
        }

        switch (OpcodeMod) {
            case (Modifiers::A) :
                Core[Destination]->AOperand = Core[Destination]->AOperand / Core[Source]->AOperand;
                break;
            case (Modifiers::AB):
                Core[Destination]->BOperand = Core[Destination]->BOperand / Core[Source]->AOperand;
                break;
            case (Modifiers::B) :
                Core[Destination]->BOperand = Core[Destination]->BOperand / Core[Source]->BOperand;
                break;
            case (Modifiers::BA):
                Core[Destination]->AOperand = Core[Destination]->AOperand / Core[Source]->BOperand;
                break;
            case (Modifiers ::I):
            case (Modifiers::F):
                Core[Destination]->AOperand = Core[Destination]->AOperand / Core[Source]->AOperand;
                Core[Destination]->BOperand = Core[Destination]->BOperand / Core[Source]->BOperand;
                break;
            case (Modifiers::X):
                Core[Destination]->BOperand = Core[Destination]->BOperand / Core[Source]->AOperand;
                Core[Destination]->AOperand = Core[Destination]->AOperand / Core[Source]->BOperand;
                break;

        }
        ((*it).Address++)%size;
        return true;
    }
    Div_command* Clone() override {
        return new Div_command(*this);
    }
};
Instruction* Divc() {
    return new Div_command;
}
/*Instruction* Diva() {
    return new Div_command();
}*/
namespace {
    bool b = Factory::get_instance()->regist3r(Opcodes::DIV, Divc);
}