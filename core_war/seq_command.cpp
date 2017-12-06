
#include "factory.hpp"
class Seq_command : public Instruction {
public:
    explicit Seq_command(Modifiers x) { Fields.OpcodeMod = x;Name = "SEQ";}
    Seq_command() = default;
    void Execution (ExecutionContext& Executor) override {
        Executor.SetOffsets(Fields);
        switch (Fields.OpcodeMod) {
            case (Modifiers::A) :
                if (Executor.getA(Fields.AOffset)==Executor.getA(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::B) :
                if (Executor.getB(Fields.AOffset)==Executor.getB(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::AB):
                if (Executor.getA(Fields.AOffset)==Executor.getB(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::BA):
                if (Executor.getB(Fields.AOffset)==Executor.getA(Fields.BOffset)) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::F):
                if (Executor.getA(Fields.AOffset)==Executor.getA(Fields.BOffset)&&Executor.getB(Fields.AOffset)==Executor.getB(Fields.BOffset) ) {
                    Executor.ForwardQueue();
                    Executor.ForwardQueue();
                    return;
                }
            case (Modifiers::X):
                if (Executor.getA(Fields.AOffset)==Executor.getB(Fields.BOffset)&&Executor.getB(Fields.AOffset)==Executor.getA(Fields.BOffset) ) {
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
    Seq_command* Clone() override {
        return new Seq_command(*this);
    }
};


namespace {
    Instruction* seqab() {return new Seq_command(Modifiers::AB);}
    Instruction* seqba() {return new Seq_command(Modifiers::BA);}
    Instruction* seqta() {return new Seq_command(Modifiers::A);}
    Instruction* seqtb() {return new Seq_command(Modifiers::B);}
    Instruction* seqtf() {return new Seq_command(Modifiers::F);}
    Instruction* seqx() {return new Seq_command(Modifiers::X);}
    Instruction* seqi() {return new Seq_command(Modifiers::I);}
    bool a = Factory::get_instance()->regist3r("SEQ.AB",&seqab);
    bool b = Factory::get_instance()->regist3r("SEQ.BA",&seqba);
    bool c = Factory::get_instance()->regist3r("SEQ.A",&seqta);
    bool d = Factory::get_instance()->regist3r("SEQ.B",&seqtb);
    bool f = Factory::get_instance()->regist3r("SEQ.F",&seqtf);
    bool e = Factory::get_instance()->regist3r("SEQ.X",&seqx);
    bool g = Factory::get_instance()->regist3r("SEQ.I",&seqi);
bool w = Factory::get_instance()->nameRegister("SEQ","SEQ");
}