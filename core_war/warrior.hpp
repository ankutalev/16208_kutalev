//
// Created by ulyssess on 24.10.17.
//

#ifndef CORE_WAR_WARRIOR_HPP
#define CORE_WAR_WARRIOR_HPP

#include "fstream"
#include "instructions.hpp"
#include "memory"
class Warrior {
    friend class MARS;
public:
    void Born(char[],size_t);
  // explicit Warrior(const std::vector<Instruction*>& in) {
    //    Instructions.resize(in.size());
    //    std::copy(in.begin(),in.end(),Instructions.begin());
   // }
    std::string Author;
    std::string Name;
private:
    int FlowCounter=1;
    std::vector<std::shared_ptr<Instruction> > Instructions;
    int StartPosition=0;
   // std::vector<std::string> PseudoInstructions;
   // std::string Author;
    //std::string Name;
};
#endif //CORE_WAR_WARRIOR_HPP
