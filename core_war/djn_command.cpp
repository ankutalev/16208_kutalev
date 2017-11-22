#include "factory.hpp"
class Djn_command : public Instruction {
public:
  explicit Djn_command(Modifiers x) { OpcodeMod = x; }
  void Execution(std::vector<Instruction *> &Core, CircularBuffer &Queue,
                 CircularBuffer::Iterator &it) override {
    size_t size = Core.size();
    SetOffsets(Core, it, size);
    if (AOperandMod == Mods::Lattice)
      AOffset = AOperand;
    if (BOperandMod == Mods::Lattice)
      BOffset = BOperand;
    switch (OpcodeMod) {
    case (Modifiers::A):
    case (Modifiers::BA):
      Core[BOffset]->AOperand--;
      (Core[BOffset]->AOperand) ? (*it).Address = AOffset
                                : ((*it).Address++) % size;
      break;
    case (Modifiers::B):
    case (Modifiers::AB):
      Core[BOffset]->BOperand--;
      (Core[BOffset]->BOperand) ? (*it).Address = AOffset
                                : ((*it).Address++) % size;
      break;
    case (Modifiers::I):
    case (Modifiers::F):
    case (Modifiers::X):
    case (Modifiers::Not):
      Core[BOffset]->AOperand--;
      Core[BOffset]->BOperand--;
      (Core[BOffset]->BOperand || Core[BOffset]->AOperand)
          ? (*it).Address = AOffset
          : (*it).Address = ((*it).Address++) % size;
      break;
    }
    if ((*it).Address == AOffset) {
      std::cout << (*it).Name << " jump to " << AOffset << " address"
                << std::endl;
    } else
      std::cout << (*it).Name << " will execute next command in  " << AOffset
                << " adress" << std::endl;
    (*it).Address %= size;
    if ((*it).Address < 0)
      (*it).Address += size;
  }
  Djn_command *Clone() override { return new Djn_command(*this); }
};
Instruction *Djnab() { return new Djn_command(Modifiers::AB); }
Instruction *Djnba() { return new Djn_command(Modifiers::BA); }
Instruction *Djnta() { return new Djn_command(Modifiers::A); }
Instruction *Djntb() { return new Djn_command(Modifiers::B); }
Instruction *Djntf() { return new Djn_command(Modifiers::F); }
Instruction *Djnx() { return new Djn_command(Modifiers::X); }
Instruction *Djni() { return new Djn_command(Modifiers::I); }

namespace {
bool a = Factory::get_instance()->regist3r("DJN.AB", &Djnab);
bool b = Factory::get_instance()->regist3r("DJN.BA", &Djnba);
bool c = Factory::get_instance()->regist3r("DJN.A", &Djnta);
bool d = Factory::get_instance()->regist3r("DJN.B", &Djntb);
bool f = Factory::get_instance()->regist3r("DJN.F", &Djntf);
bool e = Factory::get_instance()->regist3r("DJN.X", &Djnx);
bool g = Factory::get_instance()->regist3r("DJN.I", &Djni);
}
