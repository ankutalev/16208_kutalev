#include "factory.hpp"
class Div_command : public Instruction {
public:
  explicit Div_command(Modifiers x) { Fields.OpcodeMod = x; Name = "DIV"; }
  void Execution(ExecutionContext &Executor) override {
    Executor.SetOffsets(Fields);
    if (!Executor.getA(Fields.AOffset) && (Fields.OpcodeMod != Modifiers::BA) &&
        Fields.OpcodeMod != Modifiers::B) {
      Executor.DeleteFromQueue();
      return;
    }
    if (!Executor.getB(Fields.AOffset) && (Fields.OpcodeMod != Modifiers::AB) &&
        Fields.OpcodeMod != Modifiers::A) {
      Executor.DeleteFromQueue();
      return;
    }
    switch (Fields.OpcodeMod) {
    case (Modifiers::A):
      Executor.setA(Fields.BOffset,
                    Executor.getA(Fields.BOffset) /
                        Executor.getA(Fields.AOffset));
      break;

    case (Modifiers::AB):
      Executor.setB(Fields.BOffset,
                    Executor.getB(Fields.BOffset) /
                        Executor.getA(Fields.AOffset));
      break;
    case (Modifiers::B):
      Executor.setB(Fields.BOffset,
                    Executor.getB(Fields.BOffset) /
                        Executor.getB(Fields.AOffset));
      break;
    case (Modifiers::BA):
      Executor.setA(Fields.BOffset,
                    Executor.getA(Fields.BOffset) /
                        Executor.getB(Fields.AOffset));
      break;
    case (Modifiers::I):
    case (Modifiers::Not):
    case (Modifiers::F):
      Executor.setA(Fields.BOffset,
                    Executor.getA(Fields.BOffset) /
                        Executor.getA(Fields.AOffset));
      Executor.setB(Fields.BOffset,
                    Executor.getB(Fields.BOffset) /
                        Executor.getB(Fields.AOffset));
      break;
    case (Modifiers::X):
      Executor.setB(Fields.BOffset,
                    Executor.getB(Fields.BOffset) /
                        Executor.getA(Fields.AOffset));
      Executor.setA(Fields.BOffset,
                    Executor.getA(Fields.BOffset) /
                        Executor.getB(Fields.AOffset));
      break;
    }
    Executor.ForwardQueue();
  }
  Div_command *Clone() override { return new Div_command(*this); }
};

namespace {
Instruction *divab() { return new Div_command(Modifiers::AB); }
Instruction *divba() { return new Div_command(Modifiers::BA); }
Instruction *divta() { return new Div_command(Modifiers::A); }
Instruction *divtb() { return new Div_command(Modifiers::B); }
Instruction *divtf() { return new Div_command(Modifiers::F); }
Instruction *divx() { return new Div_command(Modifiers::X); }
Instruction *divi() { return new Div_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("DIV.AB", &divab);
bool b = Factory::get_instance()->regist3r("DIV.BA", &divba);
bool c = Factory::get_instance()->regist3r("DIV.A", &divta);
bool d = Factory::get_instance()->regist3r("DIV.B", &divtb);
bool f = Factory::get_instance()->regist3r("DIV.F", &divtf);
bool e = Factory::get_instance()->regist3r("DIV.X", &divx);
bool g = Factory::get_instance()->regist3r("DIV.I", &divi);
bool w = Factory::get_instance()->nameRegister("DIV","DIV");
}
