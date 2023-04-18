#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model model;
  Controller controller(&model);
  MainWindow w(&controller);
  w.show();

  return a.exec();
}
