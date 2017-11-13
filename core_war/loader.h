//
// Created by ulyssess on 21.10.17.
//

#ifndef CORE_WAR_LOADER_H
#define CORE_WAR_LOADER_H

#include <random>
#include "warrior.hpp"
#include "CircularBuffer.hpp"
//#include "template_hashtable_hpp"

class MARS {
    friend class CircularBuffer;
public:
   explicit MARS(Instruction* def) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(MinSeparation,7000);
        SeparationRange = uni(rng);
        std::cout<<SeparationRange<<std::endl;
        Initial=def;
    }
  /*explicit MARS() {
      std::random_device rd;
      std::mt19937 rng(rd());
      std::uniform_int_distribution<int> uni(MinSeparation,7000);
      SeparationRange = uni(rng);
      std::cout<<SeparationRange<<std::endl;
  }*/
    void SetConfiguration(const char*);
    void LoadCommands (std::vector<Warrior>& in);
   // void Execution (std:: vector <Warrior>& in);
  //  void Battle (std::vector <zaglushka>&,size_t);
    void Battle ();
    size_t GetMaxProcess() { return MaxProcess;}
private:
    int size = 8000;
    size_t TieCycles = 1000000;
    Instruction* Initial;
    size_t MaxLength = 300;
    size_t MaxProcess = 64;
    int MinSeparation = 300;
    int SeparationRange; //to do - rand separation
    size_t NumberOfWarriors = 2;
    std::vector<Instruction*> Core;
    std::vector<size_t> StartingPositions;
    CircularBuffer Flows = CircularBuffer(MaxProcess);
};

#endif //CORE_WAR_LOADER_H
