//#include <vector>
//#include <iostream>
#include "mars.h"
//void MARS::LoadCommands(std::vector<Warrior> &in) {
//  for (size_t i = 0; i < size; i++) {
//    Core.push_back(Initial->Clone());
//  }
//  Flow tmp;
//  for (Warrior &X : in) { // for each Warrior
//    for (size_t i = 0; i < X.Instructions.size(); i++) {
//      delete Core[(Position + i) % size];
//      Core[(Position + i) % size] =
//          X.Instructions[i].get()->Clone(); // putting instructions in core
//    }
//    tmp.Name = X.Name;
//    tmp.Author = X.Author;
//    tmp.Address = (Position + X.StartPosition) % size;
//    tmp.FlowCounter = &X.FlowCounter;
//    Flows.Insert(tmp);
//    Position = (Position + SeparationRange) % size;
//  }
//}
void MARS::Battle() {
  auto it = Flows.begin();
  ExecutionContext Executor(*this, Flows, &it);
  size_t i = 0;
  while (Flows.GameIsOn(i, TieCycles)) {
    Core[(*it).Address]->Execution(Executor);
    ++it;
    i++;
  }
   // std::cout << "POSLE " << i << " HODA SITUACIYA TAKAYA:" << std::endl;
    for (size_t i = 0; i < size; i++) {
      Core[i]->GettingCode(i);
    }

  if (i == TieCycles)
    std::cout << "NO WINNER IN THIS BLOODY WAR!!!!" << std::endl;
  else {

    it = Flows.begin();
    std::cout << "THE WINNER  IS " << (*it).Name << " BY" << (*it).Author
              << "  AFTER " << i << " TURNS" << std::endl;
  }
}
void MARS::MakeOption(const std::string &option, const std::string &value) {
  int tmp = std::stoi(value);
  if (tmp <= 0)
    throw std::runtime_error("invalid value!");
  if (option == "size")
    size = tmp;
  else if (option == "tiecycles")
    TieCycles = tmp;
  else if (option == "maxlength")
    MaxLength = tmp;
  else if (option == "maxprocess")
    MaxProcess = tmp;
  else if (option == "minrange")
    MinSeparation = tmp;
  else if (option == "range")
    SeparationRange = tmp;
  else if (option == "warriors")
    NumberOfWarriors = tmp;
  else
    throw std::runtime_error("invalid option");
}
int MARS::SetConfiguration(const char *in) {
  std::ifstream fin;
  fin.open(in);
  if (!fin.is_open())
    throw std::runtime_error("no file in directory!");
  std::string RedCode;
  std::string tmp;
  getline(fin, RedCode);
  if (RedCode != ";config") {
    std::cout << "it's not a config file; the battle will run with ICWC-94 "
                 "standart settings (if it can starts,ofc)";
    return 0;
  }
  try {
    while (fin >> RedCode) {
      getline(fin, tmp);
      MakeOption(RedCode, tmp);
    }
  } catch (std::exception &x) {
    std::cout << "Some lines were incorrect; they will be default by ICWC - 94 "
                 "standart settings";
    return 1;
  }
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(
      MinSeparation, size - 2 * NumberOfWarriors * MinSeparation);
  std::uniform_int_distribution<int> unip(0, size);
  SeparationRange = uni(rng);
  Position = unip(rng);
  return 1;
}

MARS::MARS() {
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(
      MinSeparation, size - 2 * NumberOfWarriors * MinSeparation);
  std::uniform_int_distribution<int> unip(0, size);
  SeparationRange = uni(rng);
  Position = unip(rng);
  Initial = Factory::get_instance()->create("DAT.F");
}

MARS::~MARS() {

  delete Initial;
  for (auto &i : Core)
    delete i;
}
/*int main() {

  //}
  //  catch (std::exception){
  //        throw std::runtime_error("Invalid file");
  // }
  //    X.SetConfiguration("config.redcode");
    // std:: vector<Warrior> Y;
      Instruction Imp(Opcodes:: MOV,Modifiers:: Not,Mods:: Not, Mods:: Not,
  0,1);

      std::vector<Instruction> q;
      q.push_back(Imp);
      Warrior IMP (q);
      std::vector<Warrior> warriors;
      warriors.push_back(IMP);

      X.LoadCommands(warriors); */
// Dat_command Z;
//  Mov_command Y;
/*  Instruction * Imp = Factory::get_instance()->create(Opcodes::MOV);
  Imp->AOperand = 0;
  Imp->BOperand = 1;
  Imp->BOperandMod = Mods::Dollar;
  Imp->AOperandMod = Mods::Dollar;
  Imp->OpcodeMod = Modifiers ::I;
  std::vector<Instruction*> q;
  q.push_back(Imp);
  Warrior IMP (q);*/
// Imp = new Mov_command (Opcodes:: MOV, Modifiers:: Not, Mods:: Dollar,
// Mods:: Dollar, 0, 1);
/*

    std::vector<Warrior> warriors;
    warriors.push_back(IMP);
    X.LoadCommands(warriors);
    std::cout<<"sffsaf";
 MEOWWWW <* ^_^ *>   delete Imp; */
// Instruction *D1 = new Dat_command;
//  std::vector<Instruction*> w;
/*   Instruction* D1 = Factory::get_instance()->create(Opcodes::DAT);
   Instruction* D2 = Factory::get_instance()->create(Opcodes::ADD);
   D2->AOperand=5;
   D2->BOperand = -1;
   D2->AOperandMod = Mods::Lattice;
   D2->BOperandMod= Mods::Not;
  // Instruction* D2 = new Add_command(Opcodes:: ADD, Modifiers:: Not, Mods::
  Lattice, Mods:: Not, 5, -1);
  // Instruction* D3 = new Mov_command(Opcodes:: MOV, Modifiers:: Not, Mods::
  Lattice, Mods:: Dog, 0, -2);
   Instruction* D3 = Factory::get_instance()->create(Opcodes::MOV);
   D3->Body = Opcodes ::MOV;
   D3->OpcodeMod = Modifiers ::Not;
   D3->AOperand=-2;
   D3->BOperand = -2;
   D3->BOperandMod = Mods::Dog;
  // Instruction* D4 = new Jmp_command(Mods ::Not,-2);
   Instruction* D4 = Factory::get_instance()->create(Opcodes::JMP);
   D4->AOperand=-2;

   w.push_back(D1);
   w.push_back(D2);
   w.push_back(D3);
   w.push_back(D4);
   Warrior DWARF (w);*/
//  std::vector<Warrior> warriors;
//  warriors.push_back(DWARF);
// warriors.push_back(IMP);
// X.LoadCommands(warriors);
// std::cout<<"sffsaf";
/*  while(q.GameIsOn()) {
      std::cout<<(*(*it).FlowCounter)<<std::endl;
      it++;
      if (it==q.data.end())
          it=q.data.begin();
      y++;
      if(y==3)
          it=q.DeleteCurrent(it);
  }
  //delete D1;
  //delete D2;
  //delete D3;
  //delete D4;
  delete Imp;*/
/*  return 0;
}*/
