#include "factory.hpp"
class Djn_command : public Instruction {
public:
  explicit Djn_command(Modifiers x) { Fields.OpcodeMod = x; Name = "DJN"; }
  void Execution(ExecutionContext &Executor) override {
    Executor.SetOffsets(Fields);

    if (Fields.AOperandMod == Mods::Lattice)
      Fields.AOffset = Fields.AOperand;
    if (Fields.BOperandMod == Mods::Lattice)
      Fields.BOffset = Fields.BOperand;

    switch (Fields.OpcodeMod) {
    case (Modifiers::A):
    case (Modifiers::BA):
      Executor.setA(Fields.BOffset, Executor.getA(Fields.BOffset) - 1);
      if (Executor.getA(Fields.BOffset))
        Executor.ChangeCurrentFlowAddress(Fields.AOffset);
      else
        Executor.ForwardQueue();
      break;
    case (Modifiers::B):
    case (Modifiers::AB):
      Executor.setB(Fields.BOffset, Executor.getB(Fields.BOffset) - 1);
      if (Executor.getB(Fields.BOffset))
        Executor.ChangeCurrentFlowAddress(Fields.AOffset);
      else
        Executor.ForwardQueue();
      break;
    case (Modifiers::I):
    case (Modifiers::F):
    case (Modifiers::X):
    case (Modifiers::Not):
      Executor.setB(Fields.BOffset, Executor.getB(Fields.BOffset) - 1);
      Executor.setA(Fields.BOffset, Executor.getA(Fields.BOffset) - 1);
      if (Executor.getA(Fields.BOffset) || Executor.getB(Fields.AOffset))
        Executor.ChangeCurrentFlowAddress(Fields.AOffset);
      else
        Executor.ForwardQueue();
      break;
    }

    if (Executor.getCurrentAddress() == Fields.AOffset) {
      std::cout << Executor.getCurrentWarriorName() << " jump to "
                << Fields.AOffset << " address" << std::endl;
    } else
      std::cout << Executor.getCurrentWarriorName()
                << " will execute next command in  " << Fields.AOffset
                << " adress" << std::endl;
  }

  Djn_command *Clone() override { return new Djn_command(*this); }
};

namespace {
Instruction *Djnab() { return new Djn_command(Modifiers::AB); }
Instruction *Djnba() { return new Djn_command(Modifiers::BA); }
Instruction *Djnta() { return new Djn_command(Modifiers::A); }
Instruction *Djntb() { return new Djn_command(Modifiers::B); }
Instruction *Djntf() { return new Djn_command(Modifiers::F); }
Instruction *Djnx() { return new Djn_command(Modifiers::X); }
Instruction *Djni() { return new Djn_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("DJN.AB", &Djnab);
bool b = Factory::get_instance()->regist3r("DJN.BA", &Djnba);
bool c = Factory::get_instance()->regist3r("DJN.A", &Djnta);
bool d = Factory::get_instance()->regist3r("DJN.B", &Djntb);
bool f = Factory::get_instance()->regist3r("DJN.F", &Djntf);
bool e = Factory::get_instance()->regist3r("DJN.X", &Djnx);
bool g = Factory::get_instance()->regist3r("DJN.I", &Djni);
bool w = Factory::get_instance()->nameRegister("DJN","DJN");
}
