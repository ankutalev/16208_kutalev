//
//

#ifndef CORE_WAR_FACTORY_HPP
#define CORE_WAR_FACTORY_HPP
class Factory;
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
            std::cout<<a<<std::endl;
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

    bool nameRegister(const std::string& a,const std::string& b) {
      if(namez.Contains(a))
        throw std::runtime_error("Two commands have a same name!");
      namez[a] = b;
      return true;
    }
private:
    HashTable<std::string,creator_t ,&HashCalculation> creatorzzz;
    HashTable<std::string,std::string,&HashCalculation> namez;
};
#endif //CORE_WAR_FACTORY_HPP
