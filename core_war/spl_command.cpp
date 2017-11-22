#include "factory.hpp"
#include "loader.h"

class Spl_command : public Instruction {
public:
  explicit Spl_command(Modifiers x) { OpcodeMod = x; }
  void Execution(std::vector<Instruction *> &Core, CircularBuffer &Queue,
                 CircularBuffer::Iterator &it) override {
    size_t size = Core.size();
    SetOffset(Core, it, size, AOperandMod, AOperand, &AOffset);
    if (AOperandMod == Mods::Lattice)
      AOffset = AOperand;
    if (BOperandMod == Mods::Lattice)
      BOffset = BOperand;
    if ((*(*it).FlowCounter) < Queue.GetFlowCounter()) {
      Flow tmp = (*it);
      tmp.Address = AOffset % size;
      Queue.InsertPrev(it, tmp);
    } else
      std::cout << "TOO MUCH FLOWS FOR " << (*it).Name << std::endl;
    (*it).Address = ((*it).Address + 1) % size;
  }
  Spl_command *Clone() override { return new Spl_command(*this); }
};
Instruction *splab() { return new Spl_command(Modifiers::AB); }
Instruction *splba() { return new Spl_command(Modifiers::BA); }
Instruction *splta() { return new Spl_command(Modifiers::A); }
Instruction *spltb() { return new Spl_command(Modifiers::B); }
Instruction *spltf() { return new Spl_command(Modifiers::F); }
Instruction *splx() { return new Spl_command(Modifiers::X); }
Instruction *spli() { return new Spl_command(Modifiers::I); }

namespace {
bool a = Factory::get_instance()->regist3r("SPL.AB", &splab);
bool b = Factory::get_instance()->regist3r("SPL.BA", &splba);
bool c = Factory::get_instance()->regist3r("SPL.A", &splta);
bool d = Factory::get_instance()->regist3r("SPL.B", &spltb);
bool f = Factory::get_instance()->regist3r("SPL.F", &spltf);
bool e = Factory::get_instance()->regist3r("SPL.X", &splx);
bool g = Factory::get_instance()->regist3r("SPL.I", &spli);
}