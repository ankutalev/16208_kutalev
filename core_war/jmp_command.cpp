//#include "instructions.hpp"
#include "factory.hpp"
class Jmp_command : public Instruction {
public:
  explicit Jmp_command(Modifiers x) { Fields.OpcodeMod = x;Name = "JMP"; }
    void Execution(ExecutionContext& Executor) override {
        if (Fields.AOperandMod==Mods::Lattice)
            Fields.AOffset = Fields.AOperand;
        else
            Executor.SetOffset(Fields.AOperandMod,Fields.AOperand,&Fields.AOffset);
        Executor.ChangeCurrentFlowAddress(Fields.AOffset);
        std::cout << Executor.getCurrentWarriorName() << " jump! at " <<Executor.getCurrentAddress()<<" adress"<< std::endl;
  }
  Jmp_command *Clone() override { return new Jmp_command(*this); }
};


namespace {
    Instruction *Jmpab() { return new Jmp_command(Modifiers::AB); }
    Instruction *Jmpba() { return new Jmp_command(Modifiers::BA); }
    Instruction *Jmpta() { return new Jmp_command(Modifiers::A); }
    Instruction *Jmptb() { return new Jmp_command(Modifiers::B); }
    Instruction *Jmptf() { return new Jmp_command(Modifiers::F); }
    Instruction *Jmpx() { return new Jmp_command(Modifiers::X); }
    Instruction *Jmpi() { return new Jmp_command(Modifiers::I); }
bool a = Factory::get_instance()->regist3r("JMP.AB", &Jmpab);
bool b = Factory::get_instance()->regist3r("JMP.BA", &Jmpba);
bool c = Factory::get_instance()->regist3r("JMP.A", &Jmpta);
bool d = Factory::get_instance()->regist3r("JMP.B", &Jmptb);
bool f = Factory::get_instance()->regist3r("JMP.F", &Jmptf);
bool e = Factory::get_instance()->regist3r("JMP.X", &Jmpx);
bool g = Factory::get_instance()->regist3r("JMP.I", &Jmpi);
bool w = Factory::get_instance()->nameRegister("JMP","JMP");
}