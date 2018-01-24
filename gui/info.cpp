#include "info.h"

infoWindow::infoWindow(QWidget *parent) : QWidget(parent)
{
        lay = new QVBoxLayout;
       name = new QLabel;
       command = new QLabel;
       danger = new QLabel;
       position = new QLabel;
       lay->addWidget(name);
        lay->addWidget(command);
         lay->addWidget(danger);
          lay->addWidget(position);
          setLayout(lay);
}
infoWindow::~infoWindow() {
    //delete lay;//????????????????????????????
}
void infoWindow::setName(const std::__cxx11::string &nam) {
    name->setText("Name:"+QString::fromStdString(nam));
}
void infoWindow::setCommand(const std::__cxx11::string &com) {
    command->setText("Command:"+QString::fromStdString(com));
}
void infoWindow::setDanger(bool isdanger) {
    (isdanger) ? danger->setText("DANGER!!11") : danger->setText("Not danger");
}
void infoWindow::setPosition(int x) {
    position->setText("Position: " + QString::number(x));
}
