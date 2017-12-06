#include "factory.hpp"
class Jmz_command : public Instruction {
public:
  explicit Jmz_command(Modifiers x) { Fields.OpcodeMod = x;Name = "JMZ"; }
  void Execution(ExecutionContext &Executor) override {
    if (Fields.AOperandMod == Mods::Lattice &&
        Fields.BOperandMod == Mods::Lattice) {
      Fields.AOffset = Fields.AOperand;
      Fields.BOffset = Fields.BOperand;
    } else {
      Executor.SetOffsets(Fields);
    }

    switch (Fields.OpcodeMod) {
    case (Modifiers::A):
    case (Modifiers::BA):
      if (!Executor.getA(Fields.BOffset))
        Executor.ChangeCurrentFlowAddress(Fields.AOffset);
      else
        Executor.ForwardQueue();
      break;
    case (Modifiers::Not):
    case (Modifiers::B):
    case (Modifiers::AB):
      if (!Executor.getB(Fields.BOffset)) {
        Executor.ChangeCurrentFlowAddress(Fields.AOffset);
        std::cout << Executor.getCurrentWarriorName() << " jump to "
                  << Executor.getCurrentAddress() << " address" << std::endl;
      } else {
        Executor.ForwardQueue();
        std::cout << Executor.getCurrentWarriorName()
                  << " will execute next command in  "
                  << Executor.getCurrentAddress() << " adress" << std::endl;
      }
      break;
    case (Modifiers::I):
    case (Modifiers::F):
    case (Modifiers::X):
      if (!Executor.getA(Fields.BOffset) && !Executor.getB(Fields.BOffset)) {
        Executor.ChangeCurrentFlowAddress(Fields.AOffset);
        std::cout << Executor.getCurrentWarriorName() << " jump to "
                  << Executor.getCurrentAddress() << " address" << std::endl;
      } else {
        Executor.ForwardQueue();
        std::cout << Executor.getCurrentWarriorName()
                  << " will execute next command in  "
                  << Executor.getCurrentAddress() << " adress" << std::endl;
      }
      break;
    }
  }
  Jmz_command *Clone() override { return new Jmz_command(*this); }
};

namespace {
Instruction *Jmzab() { return new Jmz_command(Modifiers::AB); }
Instruction *Jmzba() { return new Jmz_command(Modifiers::BA); }
Instruction *Jmzta() { return new Jmz_command(Modifiers::A); }
Instruction *Jmztb() { return new Jmz_command(Modifiers::B); }
Instruction *Jmztf() { return new Jmz_command(Modifiers::F); }
Instruction *Jmzx() { return new Jmz_command(Modifiers::X); }
Instruction *Jmzi() { return new Jmz_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("JMZ.AB", &Jmzab);
bool b = Factory::get_instance()->regist3r("JMZ.BA", &Jmzba);
bool c = Factory::get_instance()->regist3r("JMZ.A", &Jmzta);
bool d = Factory::get_instance()->regist3r("JMZ.B", &Jmztb);
bool f = Factory::get_instance()->regist3r("JMZ.F", &Jmztf);
bool e = Factory::get_instance()->regist3r("JMZ.X", &Jmzx);
bool g = Factory::get_instance()->regist3r("JMZ.I", &Jmzi);
bool w = Factory::get_instance()->nameRegister("JMZ","JMZ");
}