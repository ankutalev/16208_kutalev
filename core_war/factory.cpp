#include "factory.hpp"
size_t HashCalculation(const std::string &in) {
  size_t length = in.length();
  size_t HashValue = in[length - 1] % HashConst;
  for (int i = length - 2; i >= 0; i--)
    HashValue = HashValue * HashConst + in[i] % HashConst;
  return HashValue;
}
/*int main () {
    Instruction* heh = Factory::get_instance()->create(Opcodes::DAT);
    std::string h = "asd";
    heh->IsItCorrect(h);
    return 0;
}*/