#include "graph.h"

#include <vector>

#include "ui_graph.h"

Graph::Graph(Controller *control, QWidget *parent)
    : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  controller = control;
  connect(ui->draw, SIGNAL(clicked()), this, SLOT(DrawGraph()));
}

Graph::~Graph() { delete ui; }

void Graph::DrawGraph() {
  QCustomPlot *p = ui->plot;
  QVector<double> x, y;
  p->clearGraphs();
  p->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  p->xAxis->setLabel(QStringLiteral("X"));
  p->yAxis->setLabel(QStringLiteral("Y"));
  p->addGraph();
  p->graph(0)->setPen(QPen(Qt::red));
  p->graph(0)->setLineStyle(QCPGraph::lsNone);
  p->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
  if (ui->xmax->text() != "" && ui->xmin->text() != "") {
    std::pair<std::vector<double>, std::vector<double>> data =
        controller->Plot(formula.toStdString(), ui->xmin->text().toDouble(),
                         ui->xmax->text().toDouble());
    for (auto i = 0; i < 10000; ++i) {
      x.append(data.first.at(i));
      y.append(data.second.at(i));
    }
  } else {
    std::pair<std::vector<double>, std::vector<double>> data =
        controller->Plot(formula.toStdString(), -100, 100);
    for (auto i = 0; i < 10000; ++i) {
      x.append(data.first.at(i));
      y.append(data.second.at(i));
    }
  }
  p->graph(0)->addData(x, y);
  p->replot();
}

void Graph::setFormula(QString form) {
    formula = form;
}
