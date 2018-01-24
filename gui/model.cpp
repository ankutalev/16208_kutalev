#include "model.h"

model::model(QObject *parent) : QObject(parent) {}
void model::setSize(int size) { simulator.setSize(size); }
void model::setWNumbers(int number) { simulator.setNumberOfWarriors(number); }
void model::setRange(int range) { simulator.setMinSeparation(range); }
void model::load(int wnum, std::__cxx11::string *files, int size) {
  Warrior x;
  for (int i = 0; i < wnum; i++) {
    Warriors.push_back(x);
    Warriors[i].Born(files[i].c_str(), simulator.GetMaxProcess());
  }
  Loader::loadCommands(Warriors, simulator);
}
void model::startGame() { simulator.Battle(); }
std::string model::getInstructionName(int pos) {
  return simulator.getInstructionName(pos);
}
void model::coreClear() {
  simulator.coreClear();
  Loader::loadCommands(Warriors, simulator);
}
