#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "controller.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void Buttons();

  void OperationButtons();

  void CalculcateResult();

  void ButtonDot();

  void DrawPlot();

  void ButtonE();

 private:
  Ui::MainWindow *ui;
  bool dot = true;
  bool e = true;
  Controller *control;
  std::size_t bracket_count = 0;
};


#endif  // MAINWINDOW_H
