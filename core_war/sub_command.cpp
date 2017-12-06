#include "factory.hpp"
class Sub_command: public Instruction {
public:
    explicit Sub_command(Modifiers x) { Fields.OpcodeMod = x;Name = "SUB";}
    void Execution(ExecutionContext &Executor) override {
        Executor.SetOffsets(Fields);
        std::cout << Executor.getCurrentWarriorName()
                  << " make some kind of sub from: " << Fields.AOffset
                  << " to: " << Fields.BOffset << std::endl;
        switch (Fields.OpcodeMod) {
            case (Modifiers::A):
                Executor.setA(Fields.BOffset,
                              Executor.getA(Fields.AOffset) -
                              Executor.getA(Fields.BOffset));
                break;
            case (Modifiers::B):
                Executor.setB(Fields.BOffset,
                              Executor.getB(Fields.AOffset) -
                              Executor.getB(Fields.BOffset));
                break;
            case (Modifiers::AB):
                Executor.setB(Fields.BOffset,
                              Executor.getA(Fields.AOffset) -
                              Executor.getB(Fields.BOffset));
                break;
            case (Modifiers::BA):
                Executor.setA(Fields.BOffset,
                              Executor.getB(Fields.AOffset) -
                              Executor.getA(Fields.BOffset));
                break;
            case (Modifiers::Not):
            case (Modifiers::I):
            case (Modifiers::F):
                Executor.setA(Fields.BOffset,
                              Executor.getA(Fields.AOffset) -
                              Executor.getA(Fields.BOffset));
                Executor.setB(Fields.BOffset,
                              Executor.getB(Fields.AOffset) -
                              Executor.getB(Fields.BOffset));
                break;
            case (Modifiers::X):
                Executor.setB(Fields.BOffset,
                              Executor.getA(Fields.AOffset) -
                              Executor.getB(Fields.BOffset));
                Executor.setA(Fields.BOffset,
                              Executor.getB(Fields.AOffset) -
                              Executor.getA(Fields.BOffset));
                break;
        }
        Executor.ForwardQueue();
    }
    Sub_command* Clone() override {
        return new Sub_command(*this);
    }
};
namespace {
    Instruction* Subab() {return new Sub_command(Modifiers::AB);}
    Instruction* Subba() {return new Sub_command(Modifiers::BA);}
    Instruction* Subta() {return new Sub_command(Modifiers::A);}
    Instruction* Subtb() {return new Sub_command(Modifiers::B);}
    Instruction* Subtf() {return new Sub_command(Modifiers::F);}
    Instruction* Subx() {return new Sub_command(Modifiers::X);}
    Instruction* Subi() {return new Sub_command(Modifiers::I);}
    bool a = Factory::get_instance()->regist3r("SUB.AB",&Subab);
    bool b = Factory::get_instance()->regist3r("SUB.BA",&Subba);
    bool c = Factory::get_instance()->regist3r("SUB.A",&Subta);
    bool d = Factory::get_instance()->regist3r("SUB.B",&Subtb);
    bool f = Factory::get_instance()->regist3r("SUB.F",&Subtf);
    bool e = Factory::get_instance()->regist3r("SUB.X",&Subx);
    bool g = Factory::get_instance()->regist3r("SUB.I",&Subi);
bool w = Factory::get_instance()->nameRegister("SUB","SUB");
}
