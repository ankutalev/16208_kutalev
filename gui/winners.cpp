#include "winners.h"
#include "controller.h"

winners::winners(QWidget *parent) : QWidget(parent) {
  lay = new QHBoxLayout;
  winner = new QLabel;
  rematch = new QPushButton;
  rematch->setText("Rematch with those warriors");
  exit_ = new QPushButton;
  exit_->setText("EXIT FROM THESE VIETNAME");
  newGame = new QPushButton;
  newGame->setText("New game with new warriors and settings");
  lay->addWidget(winner);
  lay->addWidget(rematch);
  lay->addWidget(exit_);
  lay->addWidget(newGame);
  setLayout(lay);
  newGame->hide();
  rematch->hide();
  connect(exit_, SIGNAL(clicked()), this, SLOT(exitVietname()));
}
void winners::exitVietname() { exit(-322); }
void winners::getWinner(const std::__cxx11::string &win) {
  winner->setText(QString::fromStdString(win));
}
