//
// Created by ulyssess on 21.10.17.
//

#ifndef CORE_WAR_LOADER_H
#define CORE_WAR_LOADER_H
#include "warrior.hpp"
//#include "template_hashtable_hpp"

class MARS {
public:
    void SetConfiguration(const char*);
    void LoadCommands (std::vector<Warrior>& in);
    void Execution (std:: vector <Warrior>& in);
  //  void Battle (std::vector <zaglushka>&,size_t);
    void Battle ();
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
    std::vector<Instruction*> Core;
    std::vector<size_t> StartingPositions;
    std::vector<zaglushka > Potoki;
};

#endif //CORE_WAR_LOADER_H
