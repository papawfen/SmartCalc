#include "mainwindow.h"

#include <string>

#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->lineEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
  control = controller;
  connect(ui->lineEdit, SIGNAL(editingFinished()), this,
          SLOT(CalculcateResult()));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_ac, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_c, SIGNAL(clicked()), this, SLOT(Buttons()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_result, SIGNAL(clicked()), this, SLOT(CalculcateResult()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(ButtonDot()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_ac, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_c, SIGNAL(clicked()), this, SLOT(OperationButtons()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(ButtonE()));
  connect(ui->plotbutton, SIGNAL(clicked()), this, SLOT(DrawPlot()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::Buttons() {
  QPushButton *buttons = (QPushButton *)sender();
  QString str;
  if (ui->label_result->text() == '0' || ui->label_result->text() == "ERROR")
    ui->label_result->setText("");
  str = ui->label_result->text() + buttons->text();
  ui->label_result->setText(str);
}

void MainWindow::OperationButtons() {
  if (ui->label_result->text() == '0' || ui->label_result->text() == "ERROR")
    ui->label_result->setText("");
  QPushButton *operationButtons = (QPushButton *)sender();
  QString str;
  dot = true;
  e = true;
  if ((operationButtons->text() == '-' || operationButtons->text() == '+') &&
      ui->label_result->text().endsWith("e"))
    e = false;
  if (operationButtons->text() == "AC") {
    ui->label_result->setText("0");
  } else if (operationButtons->text() == 'C') {
    str = ui->label_result->text();
    str.chop(2);
    if (str.isEmpty()) str = "0";
    ui->label_result->setText(str);
  } else if (operationButtons->text() == ')') {
    --bracket_count;
    str = ui->label_result->text() + operationButtons->text();
    ui->label_result->setText(str);
  } else if (operationButtons->text() == '(') {
    ++bracket_count;
    str = ui->label_result->text() + operationButtons->text();
    ui->label_result->setText(str);
  } else {
    str = ui->label_result->text() + operationButtons->text();
    ui->label_result->setText(str);
  }
}

void MainWindow::ButtonDot() {
  if (dot == true)
    ui->label_result->setText(ui->label_result->text() + tr("."));
  dot = false;
}

void MainWindow::ButtonE() {
  if (e == true) ui->label_result->setText(ui->label_result->text() + tr("e"));
  e = false;
}

void MainWindow::CalculcateResult() {
  QString res;
  std::string tmp = ui->label_result->text().toStdString().insert(
      ui->label_result->text().toStdString().length(), bracket_count, ')');
  if (ui->lineEdit->text() != "") {
    res = QString::fromStdString(
        control->Calculate(tmp, ui->lineEdit->text().toDouble()));
    ui->label_result->setText(res);
  } else {
    res = QString::fromStdString(control->Calculate(tmp, 0));
  }
  ui->label_result->setText(res);
}

void MainWindow::DrawPlot() {
  Graph graph(control);
  graph.setFormula(ui->label_result->text());
  graph.exec();
}
