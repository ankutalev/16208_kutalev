
#include "factory.hpp"
class Mov_command : public Instruction {
public:
  explicit Mov_command(Modifiers x) { Fields.OpcodeMod = x; Name= "MOV";}
  void Execution(ExecutionContext &Executor) override {
    Executor.SetOffsets(Fields);
    std::cout << Executor.getCurrentWarriorName()
              << " make some kind of mov from: " << Fields.AOffset
              << " to: " << Fields.BOffset << std::endl;
    switch (Fields.OpcodeMod) {
    case (Modifiers::A):
      Executor.setA(Fields.BOffset, Executor.getA(Fields.AOffset));
      break;
    case (Modifiers::B):
      Executor.setB(Fields.BOffset, Executor.getB(Fields.AOffset));
      break;
    case (Modifiers::AB):
      Executor.setB(Fields.BOffset, Executor.getA(Fields.AOffset));
      break;
    case (Modifiers::BA):
      Executor.setA(Fields.BOffset, Executor.getB(Fields.AOffset));
      break;
    case (Modifiers::F):
      Executor.setA(Fields.BOffset, Executor.getA(Fields.AOffset));
      Executor.setB(Fields.BOffset, Executor.getB(Fields.AOffset));
      break;
    case (Modifiers::X):
      Executor.setB(Fields.BOffset, Executor.getA(Fields.AOffset));
      Executor.setA(Fields.BOffset, Executor.getB(Fields.AOffset));
      break;
    case (Modifiers::Not):
    case (Modifiers::I):
      Executor.ChangeCommand(Fields.AOffset, Fields.BOffset);
    }
    Executor.ForwardQueue();
  }
  Instruction *Clone() override { return new Mov_command(*this); }
};

namespace {
Instruction *movab() { return new Mov_command(Modifiers::AB); }
Instruction *movba() { return new Mov_command(Modifiers::BA); }
Instruction *mova() { return new Mov_command(Modifiers::A); }
Instruction *movb() { return new Mov_command(Modifiers::B); }
Instruction *movf() { return new Mov_command(Modifiers::F); }
Instruction *movx() { return new Mov_command(Modifiers::X); }
Instruction *movi() { return new Mov_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("MOV.AB", &movab);
bool b = Factory::get_instance()->regist3r("MOV.BA", &movba);
bool c = Factory::get_instance()->regist3r("MOV.A", &mova);
bool d = Factory::get_instance()->regist3r("MOV.B", &movb);
bool f = Factory::get_instance()->regist3r("MOV.F", &movf);
bool e = Factory::get_instance()->regist3r("MOV.X", &movx);
bool g = Factory::get_instance()->regist3r("MOV.I", &movi);
bool w = Factory::get_instance()->nameRegister("MOV","MOV");
}