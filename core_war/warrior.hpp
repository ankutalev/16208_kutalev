//
//

#ifndef CORE_WAR_WARRIOR_HPP
#define CORE_WAR_WARRIOR_HPP
class Warrior;
#include "fstream"
#include "instructions.hpp"
#include "memory"
class Warrior {
    friend class Loader;
public:
    void Born(char[],size_t);
private:
     int FlowCounter=1;
     std::string Author;
     std::string Name;
     std::vector<std::shared_ptr<Instruction> > Instructions;
     int StartPosition=0;
};
#endif //CORE_WAR_WARRIOR_HPP
