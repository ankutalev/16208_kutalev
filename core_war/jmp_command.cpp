//#include "instructions.hpp"
#include "factory.hpp"
class Jmp_command : public Instruction {
public:
  explicit Jmp_command(Modifiers x) { OpcodeMod = x; }
  void Execution(std::vector<Instruction *> &Core, CircularBuffer &Queue,
                 CircularBuffer::Iterator &it) override {
    size_t size = Core.size();
    SetOffset(Core, it, size, AOperandMod, AOperand, &AOffset);
    if (AOperandMod == Mods::Lattice)
      AOffset = AOperand;
    (*it).Address = AOffset % size;
    std::cout << (*it).Name << " jump to  " << (*it).Address << " adress"
              << std::endl;
    if ((*it).Address < 0)
      ((*it).Address += size);
  }
  Jmp_command *Clone() override { return new Jmp_command(*this); }
};
Instruction *Jmpab() { return new Jmp_command(Modifiers::AB); }
Instruction *Jmpba() { return new Jmp_command(Modifiers::BA); }
Instruction *Jmpta() { return new Jmp_command(Modifiers::A); }
Instruction *Jmptb() { return new Jmp_command(Modifiers::B); }
Instruction *Jmptf() { return new Jmp_command(Modifiers::F); }
Instruction *Jmpx() { return new Jmp_command(Modifiers::X); }
Instruction *Jmpi() { return new Jmp_command(Modifiers::I); }

namespace {
bool a = Factory::get_instance()->regist3r("JMP.AB", &Jmpab);
bool b = Factory::get_instance()->regist3r("JMP.BA", &Jmpba);
bool c = Factory::get_instance()->regist3r("JMP.A", &Jmpta);
bool d = Factory::get_instance()->regist3r("JMP.B", &Jmptb);
bool f = Factory::get_instance()->regist3r("JMP.F", &Jmptf);
bool e = Factory::get_instance()->regist3r("JMP.X", &Jmpx);
bool g = Factory::get_instance()->regist3r("JMP.I", &Jmpi);
}