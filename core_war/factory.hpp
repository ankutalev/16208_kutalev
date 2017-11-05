//
// Created by ulyssess on 01.11.17.
//

#ifndef CORE_WAR_FACTORY_HPP
#define CORE_WAR_FACTORY_HPP
#include "instructions.hpp"
#include "template_hash_table.hpp"

size_t ENUMhash (const Opcodes& a);
class Factory {
public:
    typedef Instruction *(*creator_t)();
    static Factory *get_instance() {
        static Factory f;
        return &f;
    }

    Instruction *create(Opcodes a) {
        //   if (creatorz.find(a)==creatorz.end())
        //   return   DefaultErrorPolicy::error();
        return creatorz[a]();
    }

    bool regist3r(Opcodes  a, creator_t create) {
        creatorz[a] = create;
        return true;
    }

private:
    //  std::unordered_map<Id, Creator> creatorz;
    HashTable<Opcodes,creator_t,&ENUMhash> creatorz;
};
#endif //CORE_WAR_FACTORY_HPP
