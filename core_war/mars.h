//
//

#ifndef CORE_WAR_LOADER_H
#define CORE_WAR_LOADER_H
class MARS;
#include <random>
#include "CircularBuffer.hpp"
#include "factory.hpp"
#include "warrior.hpp"
//#include "template_hashtable_hpp"

class MARS {
    friend class CircularBuffer;
    friend class ExecutionContext;
    friend class Loader;
public:
    MARS();
    ~MARS();
    int SetConfiguration(const char*);
    void LoadCommands(std::vector<Warrior>& in);
    void Battle();
    size_t GetMaxProcess() const { return MaxProcess; }
    void MakeOption(const std::string& option, const std::string& value);
private:
    int size = 8192;
    size_t TieCycles = 1000000;
    Instruction* Initial;
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
