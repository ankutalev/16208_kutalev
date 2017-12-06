#include "factory.hpp"

class Spl_command : public Instruction {
public:
  explicit Spl_command(Modifiers x) { Fields.OpcodeMod = x;Name = "SPL"; }
  void Execution(ExecutionContext &Executor) override {

    if (Fields.AOperandMod == Mods::Lattice)
      Fields.AOffset = Fields.AOperand;
    else
      Executor.SetOffset(Fields.AOperandMod, Fields.AOperand, &Fields.AOffset);
    Executor.AddToQueue(Fields.AOffset);
    Executor.ForwardQueue();
  }
  Spl_command *Clone() override { return new Spl_command(*this); }
};

namespace {
Instruction *splab() { return new Spl_command(Modifiers::AB); }
Instruction *splba() { return new Spl_command(Modifiers::BA); }
Instruction *splta() { return new Spl_command(Modifiers::A); }
Instruction *spltb() { return new Spl_command(Modifiers::B); }
Instruction *spltf() { return new Spl_command(Modifiers::F); }
Instruction *splx() { return new Spl_command(Modifiers::X); }
Instruction *spli() { return new Spl_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("SPL.AB", &splab);
bool b = Factory::get_instance()->regist3r("SPL.BA", &splba);
bool c = Factory::get_instance()->regist3r("SPL.A", &splta);
bool d = Factory::get_instance()->regist3r("SPL.B", &spltb);
bool f = Factory::get_instance()->regist3r("SPL.F", &spltf);
bool e = Factory::get_instance()->regist3r("SPL.X", &splx);
bool g = Factory::get_instance()->regist3r("SPL.I", &spli);
bool w = Factory::get_instance()->nameRegister("SPL","SPL");
}