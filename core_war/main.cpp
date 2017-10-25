#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
//#include <loader.h>
//#include "loader.h"

enum class Mods :int  { Lattice = 1, Dollar = 2, Dog = 3, Star = 4, Less = 5, More = 6, Open =7, Close =8, Not = 0};
enum class Modifiers :int   { A = 1, B =2, AB=3, BA=4, F=5, X=6, I=6, Not=0};
enum class Opcodes : int {
    DAT = 0,
    MOV = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    MOD = 6,
    JMP = 7,
    JMZ = 8,
    JMN = 9,
    DJN = 10,
    CMP = 11,
    SEQ = 12,
    SNE = 13,
    SLT = 14,
    SPL = 15,
    NOP = 16,
    ORG
};

class Instruction {
public:
    Instruction (Opcodes a,Modifiers b, Mods c, Mods d, int e, int f) : Body(a), OpcodeMod(b),
                                                                                  AOperandMod(c),
                                                                                  BOperandMod(d),
                                                                                  AOperand(e),
                                                                                  BOperand(f) {};
    Instruction() {}

    virtual bool Execution(std::vector<Instruction>&  core,size_t ) {}
  virtual bool GetMARSInstruction(std::ifstream &) {};
  virtual bool IsItCorrect(std::string &) {};
  size_t GettingCode (unsigned );
protected:
  Opcodes Body;
  Modifiers OpcodeMod;
  Mods AOperandMod;
  Mods BOperandMod;
  int AOperand;
  int BOperand;
  size_t CoreLocation;
};
class MOV : public Instruction {
public:
    bool Execution(std::vector<Instruction>& in,size_t CurrentAdress) override {
        switch (AOperandMod) {
            case (Mods::Dollar):
        }
    }
};
size_t Instruction::GettingCode(unsigned CoreSize) {
    size_t Code = (BOperand+CoreSize)%CoreSize + (CoreSize+AOperand)%CoreSize*10000 +
            static_cast<int>(BOperandMod)*100000000 + static_cast<int>(AOperandMod)*1000000000+
            static_cast<int>(OpcodeMod)*10000000000 + static_cast<int>(Body)*100000000000;
    return Code;
}
class PseudoInstruction  {
  bool IsItCorrect(std::string &) {
//      return (Body)
  }
};
class Warrior {
    friend class MARS;
public:
  void Born(char[]);
    Warrior(const std::vector<Instruction>& in) {
        Instructions.resize(in.size());
        std::copy(in.begin(),in.end(),Instructions.begin());
    }
private:
  std::vector<Instruction> Instructions;
  std::vector<std::string> PseudoInstructions;
  std::vector<std::string> Information;
};
void Warrior::Born(char *in) {
  std::ifstream fin;
  fin.open(in);
  if (!fin.is_open())
    std::cout << "meow" << std::endl;
  else {
    std::cout << "WARRIOR!!!" << std::endl;
    std::string RedCode;
    getline(fin, RedCode);
    if (RedCode != ";redcode")
      throw std::runtime_error("not_redcode_file");
  }
}

class MARS {
public:
    void SetConfiguration(const char*);
    void LoadCommands (std::vector<Warrior>& in);
    void Execution (std:: vector <Warrior>& in);
private:
    size_t size = 100;
    size_t TieCycles =  100000;
    Instruction Initial = Instruction(Opcodes::DAT,Modifiers::F,Mods::Lattice,Mods::Lattice,0,0);
    size_t MaxLength = 300;
    size_t MaxProcess = 64;
    size_t MinSeparation = 30;
    //size_t SeparationRange = rand()%size ; //to do - rand separation
    size_t SeparationRange = 40;
    size_t NumberOfWarriors = 2;
    std::vector<size_t> Core;
    std::vector<size_t> StartingPositions;
};
void MARS::LoadCommands(std::vector<Warrior> &in) {
    Core.resize(size);
    for (size_t i = 0; i < size ; i++)
        Core[i] = Initial.GettingCode(size); // initiate field with initial instruction
    size_t Position =rand()%size; // start position for 1st warrior
    for (Warrior X : in ) { // for each Warrior
        for(size_t i = 0; i<X.Instructions.size();i++)
            Core[(Position+i)%size]=X.Instructions[i].GettingCode(size); // putting instructions in core
        StartingPositions.push_back(Position); // remember start position
        Position=(Position+SeparationRange) % size; //start position for new warrior
    }
   /* for (size_t i = 0; i <StartingPositions.size() ; i++)
        std::cout<<StartingPositions[i]<<std::endl; */
}
void MARS::SetConfiguration(const char *in) {
    std::ifstream fin;
    fin.open(in);
    if(!fin.is_open())
        throw std::runtime_error("no_config_file");

}
int main(int argc, char *argv[]) {
    srand(time(0));
    Instruction Imp(Opcodes:: MOV,Modifiers:: Not,Mods:: Not, Mods:: Not, 0,1);
/*    std::cout<<Imp.GettingCode(8000)<<std::endl;
    Instruction Test(Opcodes::DAT,Modifiers::F,Mods::Lattice, Mods::Lattice,0,0);
    std::cout<<Test.GettingCode(8000)<<std::endl;
    Instruction Add(Opcodes:: ADD,Modifiers:: AB,Mods::Lattice,Mods:: Dollar,4,-1);
    std::cout<<Add.GettingCode(8000)<<std::endl;*/

    std::vector<Instruction> q;
    q.push_back(Imp);
    Warrior IMP (q);
    std::vector<Warrior> warriors;
    warriors.push_back(IMP);

    std::vector<Instruction> d;
    Instruction D1(Opcodes::DAT,Modifiers::F,Mods::Lattice, Mods::Lattice,0,0);
    d.push_back(D1);
    Instruction D2(Opcodes::ADD,Modifiers::AB,Mods::Lattice, Mods::Dollar,4,-1);
    d.push_back(D2);
    Instruction D3(Opcodes::MOV,Modifiers::AB,Mods::Lattice, Mods::Dog,0,-2);
    d.push_back(D3);
    Instruction D4(Opcodes::JMP,Modifiers::A,Mods::Dollar, Mods::Lattice,-2,0);
    d.push_back(D4);

    Warrior Dwarf(d);

    warriors.push_back(Dwarf);
    MARS X;
    X.LoadCommands(warriors);
 /* warriors.resize(argc);
  for (size_t i = 1; i < argc; i++)
    warriors[i - 1].Born(argv[i]);*/
  return 0;
}