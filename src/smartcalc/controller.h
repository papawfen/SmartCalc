#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <utility>

#include "smartcalc.h"

class Controller {
 public:
  explicit Controller(Model *mod) : model(mod) {}

  std::string Calculate(std::string input, double x) {
    model->setStr(input);
    model->setX(x);
    std::string result;
    try {
      result = std::to_string(model->Polka());
    } catch (...) {
      result = "ERROR";
    }
    return result;
  }

  std::pair<std::vector<double>, std::vector<double>> Plot(std::string input,
                                                           double begin,
                                                           double end) {
    model->setStr(input);
    return model->Plot(begin, end);
  }

 private:
  Model *model;
};

#endif  // CONTROLLER_H
