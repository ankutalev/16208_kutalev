#include "factory.hpp"
class Mul_command: public Instruction {
public:
    explicit Mul_command(Modifiers x){Fields.OpcodeMod=x; Name = "MUL";}
    void Execution(ExecutionContext &Executor) override {
        Executor.SetOffsets(Fields);
        std::cout << Executor.getCurrentWarriorName()
                  << " make some kind of multiply from: " << Fields.AOffset
                  << " to: " << Fields.BOffset << std::endl;
        switch (Fields.OpcodeMod) {
            case (Modifiers::A):
                Executor.setA(Fields.BOffset,
                              Executor.getA(Fields.AOffset) *
                              Executor.getA(Fields.BOffset));
                break;
            case (Modifiers::B):
                Executor.setB(Fields.BOffset,
                              Executor.getB(Fields.AOffset) *
                              Executor.getB(Fields.BOffset));
                break;
            case (Modifiers::AB):
                Executor.setB(Fields.BOffset,
                              Executor.getA(Fields.AOffset) *
                              Executor.getB(Fields.BOffset));
                break;
            case (Modifiers::BA):
                Executor.setA(Fields.BOffset,
                              Executor.getB(Fields.AOffset) *
                              Executor.getA(Fields.BOffset));
                break;
            case (Modifiers::Not):
            case (Modifiers::I):
            case (Modifiers::F):
                Executor.setA(Fields.BOffset,
                              Executor.getA(Fields.AOffset) *
                              Executor.getA(Fields.BOffset));
                Executor.setB(Fields.BOffset,
                              Executor.getB(Fields.AOffset) *
                              Executor.getB(Fields.BOffset));
                break;
            case (Modifiers::X):
                Executor.setB(Fields.BOffset,
                              Executor.getA(Fields.AOffset) *
                              Executor.getB(Fields.BOffset));
                Executor.setA(Fields.BOffset,
                              Executor.getB(Fields.AOffset) *
                              Executor.getA(Fields.BOffset));
                break;
        }
        Executor.ForwardQueue();
    }

    Mul_command* Clone() override { return new Mul_command(*this); }
};


    namespace {
        Instruction* Mulab() {return new Mul_command(Modifiers::AB);}
        Instruction* Mulba() {return new Mul_command(Modifiers::BA);}
        Instruction* Multa() {return new Mul_command(Modifiers::A);}
        Instruction* Multb() {return new Mul_command(Modifiers::B);}
        Instruction* Multf() {return new Mul_command(Modifiers::F);}
        Instruction* Mulx() {return new Mul_command(Modifiers::X);}
        Instruction* Muli() {return new Mul_command(Modifiers::I);}
        bool a = Factory::get_instance()->regist3r("MUL.AB",&Mulab);
        bool b = Factory::get_instance()->regist3r("MUL.BA",&Mulba);
        bool c = Factory::get_instance()->regist3r("MUL.A",&Multa);
        bool d = Factory::get_instance()->regist3r("MUL.B",&Multb);
        bool f = Factory::get_instance()->regist3r("MUL.F",&Multf);
        bool e = Factory::get_instance()->regist3r("MUL.X",&Mulx);
        bool g = Factory::get_instance()->regist3r("MUL.I",&Muli);
    bool w = Factory::get_instance()->nameRegister("MUL","MUL");
    }
