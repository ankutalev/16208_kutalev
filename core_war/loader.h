//
// Created by ulyssess on 21.10.17.
//

#ifndef CORE_WAR_LOADER_H
#define CORE_WAR_LOADER_H

#include <random>
#include "warrior.hpp"
#include "CircularBuffer.hpp"
#include "factory.hpp"
//#include "template_hashtable_hpp"

class MARS {
    friend class CircularBuffer;
public:
         MARS() {
             std::mt19937 rng(rd());
             std::uniform_int_distribution<int> uni(MinSeparation,size-2*NumberOfWarriors*MinSeparation);
             std::uniform_int_distribution<int> unip(0,size);
             SeparationRange = uni(rng);
             Position = unip(rng);
         }
    ~MARS() {

      delete Initial;
      for (auto &i : Core)
          delete i;
  }
    int SetConfiguration(const char*);
    void LoadCommands (std::vector<Warrior>& in);
    void Battle ();
    size_t GetMaxProcess() { return MaxProcess;}
    void MakeOption (const std::string& option, const std::string& value);
private:
    int size = 8192;
    size_t TieCycles = 1000000;
    Instruction* Initial = Factory::get_instance()->create("DAT.F");
    size_t MaxLength = 300;
    size_t MaxProcess = 64;
    int MinSeparation = 300;
    int SeparationRange = MinSeparation;
    int NumberOfWarriors = 2;
    std::vector<Instruction*> Core;
    CircularBuffer Flows = CircularBuffer(MaxProcess);
    std::random_device rd;
    int Position = 0;
};

#endif //CORE_WAR_LOADER_H
