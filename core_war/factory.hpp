//
// Created by ulyssess on 01.11.17.
//

#ifndef CORE_WAR_FACTORY_HPP
#define CORE_WAR_FACTORY_HPP

#include <map>
#include "instructions.hpp"
#include "template_hash_table.hpp"
static const int HashConst = 31;
size_t HashCalculation (const std::string& in );
class Factory {
public:
    typedef Instruction *(*creator_t)();
    static Factory *get_instance() {
        static Factory f;
        return &f;
    }

    Instruction* create(const std::string& a) {
           if (!creatorzzz.Contains(a))
                throw std::runtime_error("unknown command");
        return creatorzzz[a]();
    }

    bool regist3r(const std::string&  a, creator_t create) {
        creatorzzz[a] = create;
        return true;
    }

    bool Containz(const std::string& k) {
        return creatorzzz.Contains(k);
    }
private:
    //  std::unordered_map<Id, Creator> creatorz;
   // HashTable<Opcodes,creator_t,&ENUMhash> creatorz;
    HashTable<std::string,creator_t ,&HashCalculation> creatorzzz;
   // std:: map<std::string, creator_t> creatorzzz;
};
#endif //CORE_WAR_FACTORY_HPP
