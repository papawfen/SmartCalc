#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

#include "controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Graph;
}
QT_END_NAMESPACE

class Graph : public QDialog {
  Q_OBJECT

 public:
  Graph(Controller *controller, QWidget *parent = nullptr);
  ~Graph();
  QMainWindow main;
  void setFormula(QString form);

 private slots:
  void DrawGraph();

 private:
  Ui::Graph *ui;
  QCustomPlot *custom_plot;
  QCPGraph *graphic;
  Controller *controller;
  QString formula;
};

#endif  // GRAPH_H
