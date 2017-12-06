#include "factory.hpp"
class Jmn_command : public Instruction {
public:
  explicit Jmn_command(Modifiers x) { Fields.OpcodeMod = x; Name = "JMN"; }

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
      if (Executor.getA(Fields.BOffset))
        Executor.ChangeCurrentFlowAddress(Fields.AOffset);
      else
        Executor.ForwardQueue();
      break;
    case (Modifiers::Not):
    case (Modifiers::B):
    case (Modifiers::AB):
      if (Executor.getB(Fields.BOffset)) {
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
      if (Executor.getA(Fields.BOffset) || Executor.getB(Fields.BOffset)) {
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

  Jmn_command *Clone() override { return new Jmn_command(*this); }
};

namespace {
Instruction *Jmnab() { return new Jmn_command(Modifiers::AB); }
Instruction *Jmnba() { return new Jmn_command(Modifiers::BA); }
Instruction *Jmnta() { return new Jmn_command(Modifiers::A); }
Instruction *Jmntb() { return new Jmn_command(Modifiers::B); }
Instruction *Jmntf() { return new Jmn_command(Modifiers::F); }
Instruction *Jmnx() { return new Jmn_command(Modifiers::X); }
Instruction *Jmni() { return new Jmn_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("JMN.AB", &Jmnab);
bool b = Factory::get_instance()->regist3r("JMN.BA", &Jmnba);
bool c = Factory::get_instance()->regist3r("JMN.A", &Jmnta);
bool d = Factory::get_instance()->regist3r("JMN.B", &Jmntb);
bool f = Factory::get_instance()->regist3r("JMN.F", &Jmntf);
bool e = Factory::get_instance()->regist3r("JMN.X", &Jmnx);
bool g = Factory::get_instance()->regist3r("JMN.I", &Jmni);
bool w = Factory::get_instance()->nameRegister("JMN","JMN");
}