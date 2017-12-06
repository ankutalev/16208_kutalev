#include "factory.hpp"
#include "loader.hpp"
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "give me files!!!!!!";
    return -1;
  }
  MARS XXX;
  std::vector<Warrior> Warriors;
  Warrior x;
  int t = XXX.SetConfiguration(argv[1]);
  for (int i = 1 + t; i < argc; i++) {
    Warriors.push_back(x);
    Warriors[i - 1 - t].Born(argv[i], XXX.GetMaxProcess());
  }
  std::cout << "heh";
  Loader::loadCommands(Warriors,XXX);
  XXX.Battle();
  return 0;
}