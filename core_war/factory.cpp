#include "factory.hpp"
size_t ENUMhash (const Opcodes& a) {
    return (static_cast<size_t >(a) *31 -100500);
}
size_t HashCalculation (const std::string& in ) {
    size_t length = in.length();
    size_t HashValue = in[length-1] % HashConst;
    for(int i=length-2;i>=0;i--)
        HashValue= HashValue*HashConst+in[i]%HashConst;
    return HashValue;
}
/*int main () {
    Instruction* heh = Factory::get_instance()->create(Opcodes::DAT);
    std::string h = "asd";
    heh->IsItCorrect(h);
    return 0;
}*/