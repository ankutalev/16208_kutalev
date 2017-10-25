//
// Created by ulyssess on 24.10.17.
//

#ifndef CORE_WAR_WARRIOR_HPP
#define CORE_WAR_WARRIOR_HPP

#include "fstream"
#include "instructions.hpp"

class Warrior {
    friend class MARS;
public:
    void Born(char[]);
    Warrior(const std::vector<Instruction*>& in) {
        Instructions.resize(in.size());
        std::copy(in.begin(),in.end(),Instructions.begin());
    }
private:
    std::vector<Instruction*> Instructions;
    std::vector<std::string> PseudoInstructions;
    std::vector<std::string> Information;
};
#endif //CORE_WAR_WARRIOR_HPP
