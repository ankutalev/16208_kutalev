#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "/home/ulyssess/qtProjects/core_war/renderarea.h"
#include <info.h>
#include <winners.h>
#include <QDesktopWidget>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QScrollBar>
#include <iostream>
#include "controller.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  controller::get_instance()->setView(*this, 0, nullptr);
  ui->speedDown->hide();
  ui->speedUp->hide();
  connect(ui->speedDown, SIGNAL(released()), ui->rArea, SLOT(speedDownClick()));
  connect(ui->speedUp, SIGNAL(released()), ui->rArea, SLOT(speedUpClick()));

  filesErrors[0] = ui->error1;
  filesErrors[1] = ui->error2;
  filesErrors[2] = ui->error3;
  filesErrors[3] = ui->error4;
  filesErrors[4] = ui->error5;
  filesErrors[5] = ui->error6;

  // controller::setView(*this,0,nullptr);
  // parent
  //  ui->rArea = new RenderArea;
  ui->gridLayout->setAlignment(Qt::AlignRight);
  // ui->pushButton_2->hide();
  ui->lineEdit_13->hide();
  ui->lineEdit_14->hide();
  ui->lineEdit_15->hide();
  ui->lineEdit_11->hide();
  ui->label_20->hide();
  ui->label_21->hide();
  ui->label_22->hide();
  ui->label_23->hide();
  ui->error1->setStyleSheet("color: rgb(100, 0, 0)");
  ui->error2->setStyleSheet("color: rgb(100, 0, 0)");
  ui->error3->setStyleSheet("color: rgb(100, 0, 0)");
  ui->error4->setStyleSheet("color: rgb(100, 0, 0)");
  ui->error5->setStyleSheet("color: rgb(100, 0, 0)");
  ui->error6->setStyleSheet("color: rgb(100, 0, 0)");
  ui->error7->setStyleSheet("color: rgb(100, 0, 0)");
  ui->error8->setStyleSheet("color: rgb(100, 0, 0)");
  ui->error1->hide();
  ui->error2->hide();
  ui->error3->hide();
  ui->error4->hide();
  ui->error5->hide();
  ui->error6->hide();
  ui->error7->hide();
  ui->error8->hide();
  ui->lineEdit_3->setValidator(new QIntValidator);
  ui->lineEdit_4->setValidator(new QIntValidator);
}
MainWindow::~MainWindow() { delete ui; }

// void MainWindow::on_comboBox_2_activated(int index)
//{
//    switch (index) {
//    case (4):
//        std::cout<<"6?";
//        ui->lineEdit_8->setText("huy zalupa");
//        ui->lineEdit_9->show();
//        ui->lineEdit_10->show();
//        ui->lineEdit_11->show();
//        ui->lineEdit_12->show();
//        repaint();
//        break;
//    case(3):
//        std::cout<<"5?";
//        ui->lineEdit_9->show();
//        ui->lineEdit_10->show();
//        ui->lineEdit_11->show();
//        break;
//    case(2):
//        std::cout<<"4?";
//        ui->lineEdit_9->show();
//        ui->lineEdit_10->show();
//        break;
//    case(1):
//        ui->lineEdit_9->show();
//        std::cout<<"3?";
//        break;
//    }
//}

void MainWindow::on_comboBox_activated(int index) {
  switch (index) {
    case (4):
      ui->lineEdit_13->show();
      ui->lineEdit_14->show();
      ui->lineEdit_15->show();
      ui->lineEdit_11->show();
      ui->label_20->show();
      ui->label_21->show();
      ui->label_22->show();
      ui->label_23->show();
      break;
    case (3):
      std::cout << "5?";
      ui->lineEdit_13->show();
      ui->lineEdit_14->show();
      ui->lineEdit_15->show();
      ui->lineEdit_11->hide();
      ui->label_20->show();
      ui->label_21->show();
      ui->label_22->show();
      ui->label_23->hide();
      break;
    case (2):
      std::cout << "4?";
      ui->lineEdit_13->show();
      ui->lineEdit_14->show();
      ui->lineEdit_15->hide();
      ui->lineEdit_11->hide();
      ui->label_20->show();
      ui->label_21->show();
      ui->label_22->hide();
      ui->label_23->hide();
      break;
    case (1):
      ui->lineEdit_13->show();
      ui->lineEdit_14->hide();
      ui->lineEdit_15->hide();
      ui->lineEdit_11->hide();
      ui->label_20->show();
      ui->label_21->hide();
      ui->label_22->hide();
      ui->label_23->hide();
      std::cout << "3?";
      break;
    case (0):
      ui->lineEdit_13->hide();
      ui->lineEdit_14->hide();
      ui->lineEdit_15->hide();
      ui->lineEdit_11->hide();
      ui->label_20->hide();
      ui->label_21->hide();
      ui->label_22->hide();
      ui->label_23->hide();
  }
  for (int i = 0; i < 6; i++) filesErrors[i]->hide();
}

void MainWindow::on_checkBox_2_clicked() {
  ui->checkBox->setChecked(false);
  ui->comboBox->setEnabled(true);
  on_comboBox_activated(0);
  ui->comboBox->setCurrentIndex(0);
  ui->lineEdit_3->setEnabled(true);
  ui->lineEdit_4->setEnabled(true);
}

// void MainWindow::on_comboBox_activated(int index)
//{

//}
void MainWindow::sizeError(const std::string& message) {
  std::string x =
      "Size must be larger for this input! To you settings at least ";
  x += message;
  QMessageBox::information(this, "Error", x.c_str());
}
void MainWindow::separationError() {
  ui->error8->setText(
      "Invalid separation range! It must be in 1 to size -1 range");
  ui->error8->show();
}

void MainWindow::on_checkBox_clicked() {
  ui->checkBox_2->setChecked(false);
  on_comboBox_activated(0);
  ui->comboBox->setCurrentIndex(0);
  ui->comboBox->setEnabled(false);
  ui->lineEdit_3->setEnabled(false);
  ui->lineEdit_3->setText("8192");
  ui->lineEdit_4->setEnabled(false);
  ui->lineEdit_4->setText("300");
}

void MainWindow::on_pushButton_clicked() {
  int wNum = ui->comboBox->currentText().toInt();
  std::string files[6];
  files[0] = ui->lineEdit->text().toStdString();
  files[1] = ui->lineEdit_2->text().toStdString();
  files[2] = ui->lineEdit_13->text().toStdString();
  files[3] = ui->lineEdit_14->text().toStdString();
  files[4] = ui->lineEdit_15->text().toStdString();
  files[5] = ui->lineEdit_11->text().toStdString();
  //    ui->scrollArea->horizontalScrollBar()->hide();
  //    ui->scrollArea->verticalScrollBar()->hide();
  ui->rArea->setSize(ui->lineEdit_3->text().toInt());
  controller::get_instance()->checkStartOptions(wNum, files,
                                                ui->lineEdit_3->text().toInt(),
                                                ui->lineEdit_4->text().toInt());
}
void MainWindow::reOrganize() {
  ui->pushButton->hide();
  ui->gridWidget->hide();
  ui->speedDown->show();
  ui->speedUp->show();
  ui->rArea->setMinimumSize(ui->rArea->getAreaWidth(),
                            ui->rArea->getAreaHeight());
}
void MainWindow::off() {
  // ui->rArea->ButtonClick();
  exit(0);
}

void MainWindow::filesError(const char* message) {
  // std::cout<<"dorou";
  //  std::string x = "Size must be larger for this input! To you settings at
  //  least ";
  //  x+= message;
  QMessageBox::information(this, "Error", message);
}
void MainWindow::filesOpenError(const std::string& file) {
  std::string x = "Can't open this  file: ";
  x += file;
  QMessageBox::information(this, "Error", x.c_str());
}
void MainWindow::controllerCommand(int Warrior, int Address, bool isDanger) {
  ui->rArea->ControlCommand(Warrior, Address, isDanger);
}
void MainWindow::rezults(const std::string& win) {
  ui->rArea->repaint();
  winners* rez = new winners;
  rez->setWindowTitle("Results");
  rez->getWinner(win);
  QRect rect = QApplication::desktop()->availableGeometry(rez);
  rez->move(rect.width() / 2 - rez->width() / 2,
            rect.height() / 2 - rez->height() / 2);
  // QRect desktopRect = QApplication::desktop()->availableGeometry(rez);
  // QPoint center = desktopRect.center();
  // move(center.x() - width() * 0.5, center.y() - height());
  // rez->setGeometry();
  //  QApplication::desktop()->screenGeometry(rez);
  QMessageBox info;
  info.setDefaultButton(QMessageBox::Ok);
  QPushButton* repeat = info.addButton(
      QString::fromStdString("Repeat battle with those warriors"),
      QMessageBox::NoRole);
  QPushButton* leave = info.addButton(
      QString::fromStdString("Leave this Vietnam"), QMessageBox::YesRole);
  QPushButton* newgame = info.addButton(
      QString::fromStdString("Start new game with new warriors and settings"),
      QMessageBox::AcceptRole);
  info.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
  info.setWindowTitle("Rezults");
  info.setDefaultButton(leave);
  info.setText(QString::fromStdString(win));
  info.exec();
  //   connect(repeat,SIGNAL(pressed()),ui->rArea,SLOT(tick()));
  if (info.clickedButton() == leave) exit(22);
  if (info.clickedButton() == repeat) {
    ui->rArea->tick();
    controller::get_instance()->repeat();
  }
  if (info.clickedButton() == newgame) {
    throw std::runtime_error("heh");
  }
  // QMessageBox::information(this, "Rezults", win.c_str());
  // rez->show();
}

void MainWindow::on_actionExit_triggered() { exit(22); }
