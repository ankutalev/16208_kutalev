#include "controller.h"
#include <fstream>
#include <iostream>
#include "mainwindow.h"

#include <QtCore/QCoreApplication>
controller* controller::get_instance() {
  static controller C;
  return &C;
}
void controller::setModel(model* a) { simulator = a; }

void controller::setView(MainWindow& window, int argc, char** argv) {
  argcc = argc;
  argvv = argv;
  view = &window;
  start = false;
}

void controller::getChangedCell(const std::string& Name, int Address,
                                bool isDanger) {
  view->controllerCommand(Warriors[Name], Address, isDanger);
}

bool controller::startDrawing() { return controller::start; }

void controller::warriorRegister(const std::__cxx11::string& name, int Pos) {
  Warriors.insert(std::pair<std::string, int>(name, Pos));
}

void controller::signalToStart(int wnum, std::__cxx11::string* files,
                               int size) {
  controller::start = true;
  try {
    simulator->load(wnum, files, size);
  } catch (std::exception& t) {
    controller::start = false;
    view->filesError(t.what());
  }
  if (controller::start) {
    msize = size;
    this->wnum = wnum;
    mfiles = files;
    view->reOrganize();
    simulator->startGame();
  }
}

void controller::checkStartOptions(int warNum, std::string* files, int size,
                                   int separation) {
  simulator->setRange(separation);
  simulator->setWNumbers(warNum);
  try {
    simulator->setSize(size);
  } catch (std::runtime_error& x) {
    view->sizeError(x.what());
    return;
  }
  for (int i = 0; i < warNum; i++) {
    std::ifstream checkFile(files[i]);
    if (!checkFile.is_open()) {
      view->filesOpenError(files[i]);
      return;
    }
  }
  signalToStart(warNum, files, size);
}
std::string controller::getWName(int pos) {
  if (pos == -1) return "this is MARS base field";
  for (auto& it : Warriors)
    if (it.second == pos) return it.first;
}
std::string controller::getCommandName(int pos) {
  return simulator->getInstructionName(pos);
}
void controller::warEnd(const std::__cxx11::string& win) { view->rezults(win); }
void controller::repeat() {
  Warriors.clear();
  simulator->coreClear();
  simulator->startGame();
}
