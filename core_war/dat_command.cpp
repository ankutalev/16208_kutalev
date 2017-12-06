#include "factory.hpp"
class Dat_command : public Instruction {
public:
  explicit Dat_command(Modifiers x) { Fields.OpcodeMod = x; Name = "DAT"; }
  void Execution(ExecutionContext &Executor) override {
    std::cout << Executor.getCurrentWarriorName() << "    BLOW UP!!! AT "<<Executor.getCurrentAddress()
              << std::endl;
    Executor.DeleteFromQueue();
  }
  Instruction *Clone() override { return new Dat_command(*this); }
};

namespace {
Instruction *datab() { return new Dat_command(Modifiers::AB); }
Instruction *datba() { return new Dat_command(Modifiers::BA); }
Instruction *data() { return new Dat_command(Modifiers::A); }
Instruction *datb() { return new Dat_command(Modifiers::B); }
Instruction *datf() { return new Dat_command(Modifiers::F); }
Instruction *datx() { return new Dat_command(Modifiers::X); }
Instruction *dati() { return new Dat_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("DAT.AB", &datab);
bool b = Factory::get_instance()->regist3r("DAT.BA", &datba);
bool c = Factory::get_instance()->regist3r("DAT.A", &data);
bool d = Factory::get_instance()->regist3r("DAT.B", &datb);
bool f = Factory::get_instance()->regist3r("DAT.F", &datf);
bool e = Factory::get_instance()->regist3r("DAT.X", &datx);
bool g = Factory::get_instance()->regist3r("DAT.I", &dati);
bool w = Factory::get_instance()->nameRegister("DAT","DAT");
}