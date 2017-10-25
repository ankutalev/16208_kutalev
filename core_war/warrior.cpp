//
// Created by ulyssess on 24.10.17.
//



#include "warrior.hpp"

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