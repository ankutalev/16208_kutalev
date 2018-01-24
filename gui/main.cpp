#include <QApplication>
#include "controller.h"
#include "mainwindow.h"
int main(int argc, char* argv[]) {
  model XXX;
  controller::get_instance()->setModel(&XXX);
  QApplication a(argc, argv);
  MainWindow w;
  try {
    w.show();
    a.exec();
  } catch (std::exception& a) {
    w.hide();
    main(argc, argv);
  }
  return 0;
}
