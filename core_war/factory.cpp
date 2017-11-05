#include "factory.hpp"
size_t ENUMhash (const Opcodes& a) {
    return (static_cast<size_t >(a) *31 -100500);
}
/*int main () {
    Instruction* heh = Factory::get_instance()->create(Opcodes::DAT);
    std::string h = "asd";
    heh->IsItCorrect(h);
    return 0;
}*/