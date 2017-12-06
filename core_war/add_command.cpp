#include "factory.hpp"
class Add_command : public Instruction {
public:
  explicit Add_command(Modifiers x) { Fields.OpcodeMod = x; Name = "ADD"; }
  void Execution(ExecutionContext &Executor) override {
    Executor.SetOffsets(Fields);
    std::cout << Executor.getCurrentWarriorName()
              << " make some kind of add from: " << Fields.AOffset
              << " to: " << Fields.BOffset << std::endl;
    switch (Fields.OpcodeMod) {
    case (Modifiers::A):
      Executor.setA(Fields.BOffset,
                    Executor.getA(Fields.AOffset) +
                        Executor.getA(Fields.BOffset));
      break;
    case (Modifiers::B):
      Executor.setB(Fields.BOffset,
                    Executor.getB(Fields.AOffset) +
                        Executor.getB(Fields.BOffset));
      break;
    case (Modifiers::AB):
      Executor.setB(Fields.BOffset,
                    Executor.getA(Fields.AOffset) +
                        Executor.getB(Fields.BOffset));
      break;
    case (Modifiers::BA):
      Executor.setA(Fields.BOffset,
                    Executor.getB(Fields.AOffset) +
                        Executor.getA(Fields.BOffset));
      break;
    case (Modifiers::Not):
    case (Modifiers::I):
    case (Modifiers::F):
      Executor.setA(Fields.BOffset,
                    Executor.getA(Fields.AOffset) +
                        Executor.getA(Fields.BOffset));
      Executor.setB(Fields.BOffset,
                    Executor.getB(Fields.AOffset) +
                        Executor.getB(Fields.BOffset));
      break;
    case (Modifiers::X):
      Executor.setB(Fields.BOffset,
                    Executor.getA(Fields.AOffset) +
                        Executor.getB(Fields.BOffset));
      Executor.setA(Fields.BOffset,
                    Executor.getB(Fields.AOffset) +
                        Executor.getA(Fields.BOffset));
      break;
    }
    Executor.ForwardQueue();
  }
  Add_command *Clone() override { return new Add_command(*this); }
};

namespace {
Instruction *addab() { return new Add_command(Modifiers::AB); }
Instruction *addba() { return new Add_command(Modifiers::BA); }
Instruction *addta() { return new Add_command(Modifiers::A); }
Instruction *addtb() { return new Add_command(Modifiers::B); }
Instruction *addtf() { return new Add_command(Modifiers::F); }
Instruction *addx() { return new Add_command(Modifiers::X); }
Instruction *addi() { return new Add_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("ADD.AB", &addab);
bool b = Factory::get_instance()->regist3r("ADD.BA", &addba);
bool c = Factory::get_instance()->regist3r("ADD.A", &addta);
bool d = Factory::get_instance()->regist3r("ADD.B", &addtb);
bool f = Factory::get_instance()->regist3r("ADD.F", &addtf);
bool e = Factory::get_instance()->regist3r("ADD.X", &addx);
bool g = Factory::get_instance()->regist3r("ADD.I", &addi);
bool w = Factory::get_instance()->nameRegister("ADD","ADD");
}
