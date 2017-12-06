//
// Created by ulyssess on 24.10.17.
//




#include "instructions.hpp"

/*bool Mov_command::Execution(std::vector<Instruction> & Core, size_t Address) override {
   /* size_t size = Core.size();
    size_t Destination = BOperand;
    size_t Source = AOperand;
   /* switch (BOperandMod) { //to do for other operand mods (not only # and $)
        case (Mods::Dollar):
            Destination = (Destination +Address)%size;
        case (Mods::Lattice):
    }
    if (BOperandMod==Mods::Dollar)
        Destination = (Destination + Address)%size;
    if(AOperandMod==Mods::Dollar)
        Source = (Source+Address)%size;
    */
   // Core[Destination]=Core[Source];
   // return true;


/*bool Dat_command::Execution(std::vector<Instruction*> &Core, size_t Address) {
    return false;
}*/
bool Instruction::nameRegister() {
  return Factory::get_instance()->nameRegister(Name,Name);
}
