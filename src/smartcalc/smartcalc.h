#ifndef BACK_SMARTCALC_H
#define BACK_SMARTCALC_H

#include <cmath>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "tokens.h"

class Model {
 public:
  Model() : str(""), x(0) {}
  double Polka();
  std::pair<std::vector<double>, std::vector<double>> Plot(double begin,
                                                           double end);
  void setStr(const std::string& str);
  void setX(const double& x);

 private:
  std::string str;
  double x;
  std::list<Tokens> tokens;
  std::deque<std::string> functions = {"cos",  "sin",  "tan", "acos", "asin",
                                       "atan", "sqrt", "ln",  "log"};
  std::stack<std::string> function;
  std::stack<double> numbers;
  void UnarCheck(std::size_t pos);
  int CalculateBrackets(int last);
  int CalculateExpression(int last, int current);
  void InputValidation();
  static int CheckPriority(const std::string& oper);
  void StringDivision();
  std::size_t ParseNumbers(std::size_t pos);
  std::size_t ParseFunctions(std::size_t pos);
  void CalculateFunctions(const std::string& function);
  void CalculateOperators(const std::string& oper);
};

#endif  // BACK_SMARTCALC_H
