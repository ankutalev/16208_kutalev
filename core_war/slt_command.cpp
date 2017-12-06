
#include "factory.hpp"
class Slt_command : public Instruction {
public:
    explicit Slt_command(Modifiers x) { Fields.OpcodeMod = x;Name = "SLT";}


    void Execution (ExecutionContext& Executor) override {
        Executor.SetOffsets(Fields);
        switch (Fields.OpcodeMod) {
            case (Modifiers::A) :
                if (Executor.getA(Fields.AOffset)<Executor.getA(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::Not):
            case (Modifiers::B) :
                if (Executor.getB(Fields.AOffset)<Executor.getB(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::AB):
                if (Executor.getA(Fields.AOffset)<Executor.getB(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::BA):
                if (Executor.getB(Fields.AOffset)<Executor.getA(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::F):
            case (Modifiers::I):
                if (Executor.getA(Fields.AOffset)<Executor.getA(Fields.BOffset)||Executor.getB(Fields.AOffset)<Executor.getB(Fields.BOffset) ) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::X):
                if (Executor.getA(Fields.AOffset)<Executor.getB(Fields.BOffset)||Executor.getB(Fields.AOffset)<Executor.getA(Fields.BOffset) ) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
        }
        Executor.ForwardQueue();
    }
    Slt_command* Clone() override {
        return new Slt_command(*this);
    }
};


namespace {
    Instruction* sltab() {return new Slt_command(Modifiers::AB);}
    Instruction* sltba() {return new Slt_command(Modifiers::BA);}
    Instruction* sltta() {return new Slt_command(Modifiers::A);}
    Instruction* slttb() {return new Slt_command(Modifiers::B);}
    Instruction* slttf() {return new Slt_command(Modifiers::F);}
    Instruction* sltx() {return new Slt_command(Modifiers::X);}
    Instruction* slti() {return new Slt_command(Modifiers::I);}
    bool a = Factory::get_instance()->regist3r("SLT.AB",&sltab);
    bool b = Factory::get_instance()->regist3r("SLT.BA",&sltba);
    bool c = Factory::get_instance()->regist3r("SLT.A",&sltta);
    bool d = Factory::get_instance()->regist3r("SLT.B",&slttb);
    bool f = Factory::get_instance()->regist3r("SLT.F",&slttf);
    bool e = Factory::get_instance()->regist3r("SLT.X",&sltx);
    bool g = Factory::get_instance()->regist3r("SLT.I",&slti);
bool w = Factory::get_instance()->nameRegister("SLT","SLT");
}