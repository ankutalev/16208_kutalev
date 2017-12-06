
#include "factory.hpp"
class Sne_command : public Instruction {
public:
    explicit Sne_command(Modifiers x) { Fields.OpcodeMod = x; Name = "SNE";}
    void Execution (ExecutionContext& Executor) override {
        Executor.SetOffsets(Fields);
        switch (Fields.OpcodeMod) {
            case (Modifiers::A) :
                if (Executor.getA(Fields.AOffset)!=Executor.getA(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::B) :
                if (Executor.getB(Fields.AOffset)!=Executor.getB(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::AB):
                if (Executor.getA(Fields.AOffset)!=Executor.getB(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::BA):
                if (Executor.getB(Fields.AOffset)!=Executor.getA(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::F):
                if (Executor.getA(Fields.AOffset)!=Executor.getA(Fields.BOffset)&&Executor.getB(Fields.AOffset)!=Executor.getB(Fields.BOffset) ) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::X):
                if (Executor.getA(Fields.AOffset)!=Executor.getB(Fields.BOffset)||Executor.getB(Fields.AOffset)!=Executor.getA(Fields.BOffset) ) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::Not):
            case (Modifiers ::I):
                if(Executor.isInstructionsEqual(Fields.AOffset,Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
        }
        Executor.ForwardQueue();
    }


    Sne_command* Clone() override {
        return new Sne_command(*this);
    }
};


namespace {
    Instruction* sneab() {return new Sne_command(Modifiers::AB);}
    Instruction* sneba() {return new Sne_command(Modifiers::BA);}
    Instruction* sneta() {return new Sne_command(Modifiers::A);}
    Instruction* snetb() {return new Sne_command(Modifiers::B);}
    Instruction* snetf() {return new Sne_command(Modifiers::F);}
    Instruction* snex() {return new Sne_command(Modifiers::X);}
    Instruction* snei() {return new Sne_command(Modifiers::I);}
    bool a = Factory::get_instance()->regist3r("SNE.AB",&sneab);
    bool b = Factory::get_instance()->regist3r("SNE.BA",&sneba);
    bool c = Factory::get_instance()->regist3r("SNE.A",&sneta);
    bool d = Factory::get_instance()->regist3r("SNE.B",&snetb);
    bool f = Factory::get_instance()->regist3r("SNE.F",&snetf);
    bool e = Factory::get_instance()->regist3r("SNE.X",&snex);
    bool g = Factory::get_instance()->regist3r("SNE.I",&snei);
bool w = Factory::get_instance()->nameRegister("SNE","SNE");
}