#include "smartcalc.h"

#include <iostream>

void Model::StringDivision() {
  std::size_t pos = 0;
  tokens.clear();
  while (pos < str.length()) {
    if (str.find_first_of("*/%", pos) == pos) {
      Tokens token(str.substr(pos, 1), 4);
      tokens.push_back(token);
      ++pos;
    } else if (str.find_first_of("+-", pos) == pos) {
      UnarCheck(pos);
      Tokens token(str.substr(pos, 1), 2);
      tokens.push_back(token);
      ++pos;
    } else if (str[pos] == '^') {
      Tokens token(str.substr(pos, 1), 5);
      tokens.push_back(token);
      ++pos;
    } else if (str.find_first_of("()", pos) == pos) {
      Tokens token(str.substr(pos, 1), 1);
      tokens.push_back(token);
      ++pos;
    } else if (str[pos] == 'x') {
      Tokens token(std::to_string(x));
      tokens.push_back(token);
      ++pos;
    } else if (str.find_first_of("1234567890.e", pos) == pos) {
      pos = ParseNumbers(pos);
    } else if (str[pos] == '~') {
      Tokens token(str.substr(pos, 1), 6);
      tokens.push_back(token);
      ++pos;
    } else {
      pos = ParseFunctions(pos);
    }
  }
}

std::size_t Model::ParseNumbers(std::size_t pos) {
  std::string tmp;
  while (str.find_first_of("1234567890.e", pos) == pos) {
    tmp += str.substr(pos, 1);
    ++pos;
    if ((str[pos - 1] == 'e' && str[pos] == '-') ||
        (str[pos - 1] == 'e' && str[pos] == '+')) {
      tmp += str.substr(pos, 1);
      ++pos;
    }
  }
  Tokens token(tmp);
  tokens.push_back(token);
  return pos;
}

std::size_t Model::ParseFunctions(std::size_t pos) {
  for (std::string func : functions) {
    if (!str.compare(pos, func.length(), func)) {
      Tokens token(str.substr(pos, func.length()), 3);
      tokens.push_back(token);
      return pos + func.length();
    } else {
        throw std::invalid_argument("invalid input string");
    }
  }
  return 0;
}

void Model::InputValidation() {
  auto check = tokens.begin();
  std::string prev = check->getFunction();
  ++check;
  for (; check != tokens.end(); ++check) {
    if (!prev.find_first_of("-+^*/%") &&
        !check->getFunction().find_first_of("-+^*/%)") && prev.length() == 1) {
      throw std::invalid_argument("invalid input string");
    } else if (!prev.find_first_of(".e1234567890") &&
               !check->getFunction().find_first_of("(cstal") &&
               prev.length() > 1) {
      throw std::invalid_argument("invalid input string");
    } else if (!prev.find_first_of(")") &&
               !check->getFunction().find_first_of(".e1234567890")) {
      throw std::invalid_argument("invalid input string");
    }
    prev = check->getFunction();
  }
}

void Model::UnarCheck(std::size_t pos) {
  if (str[pos] == '-' && (pos == 0)) {
    str[pos] = '~';
  } else if (str[pos] == '-' && (str[pos - 1] == '(')) {
    str[pos] = '~';
  }
}

double Model::Polka() {
  StringDivision();
  InputValidation();
  bool first_flag = true;
  int last = 0;
  for (const auto& olkaha : tokens) {
    if (olkaha.getPriority() == -1) {
      numbers.push(stod(olkaha.getFunction()));
      continue;
    } else if (first_flag) {
      function.push(olkaha.getFunction());
      last = olkaha.getPriority();
      first_flag = false;
      continue;
    }
    if (olkaha.getFunction() == "(") {
      function.push(olkaha.getFunction());
      last = olkaha.getPriority();
    } else if (olkaha.getFunction() == ")") {
      last = CalculateBrackets(last);
      if (!function.empty() && !function.top().find_first_of("cstal")) {
        CalculateExpression(last, 3);
      }
    } else if (olkaha.getFunction() == "^") {
      function.push(olkaha.getFunction());
      last = olkaha.getPriority();
    } else if (!olkaha.getFunction().find_first_of("cstal~")) {
      function.push(olkaha.getFunction());
      last = olkaha.getPriority();
    } else {
      if (olkaha.getPriority() > last) {
        function.push(olkaha.getFunction());
        last = olkaha.getPriority();
      } else {
        CalculateExpression(last, olkaha.getPriority());
        function.push(olkaha.getFunction());
        last = olkaha.getPriority();
      }
    }
    if (function.empty()) first_flag = true;
  }
  while (!function.empty()) {
    last = CalculateExpression(last, CheckPriority(function.top()));
  }
  return numbers.top();
}

std::pair<std::vector<double>, std::vector<double>> Model::Plot(
    double begin, double end) {
  std::vector<double> x_values, y_values;
  double step = fabs(end - begin) / 10000;
  for (double new_x = begin; new_x < end; new_x += step) {
    x = new_x;
    y_values.push_back(Polka());
    x_values.push_back(x);
  }
  return std::make_pair(x_values, y_values);
}

void Model::CalculateFunctions(const std::string& func) {
  if (numbers.empty()) throw std::invalid_argument("stack is empty");
  double res = numbers.top();
  numbers.pop();
  if (func == "sin") {
    numbers.push(sin(res));
  } else if (func == "cos") {
    numbers.push(cos(res));
  } else if (func == "tan") {
    numbers.push(tan(res));
  } else if (func == "asin") {
    numbers.push(asin(res));
  } else if (func == "acos") {
    numbers.push(acos(res));
  } else if (func == "atan") {
    numbers.push(atan(res));
  } else if (func == "log") {
    numbers.push(log10(res));
  } else if (func == "ln") {
    numbers.push(log(res));
  } else if (func == "sqrt") {
    numbers.push(sqrt(res));
  } else if (func == "~") {
    numbers.push(-res);
  }
  function.pop();
}

void Model::CalculateOperators(const std::string& oper) {
  if (numbers.empty()) throw std::invalid_argument("stack is empty");
  double a = numbers.top();
  numbers.pop();
  if (numbers.empty()) throw std::invalid_argument("stack is empty");
  double b = numbers.top();
  numbers.pop();
  if (oper == "+") {
    numbers.push(b + a);
  } else if (oper == "-") {
    numbers.push(b - a);
  } else if (oper == "*") {
    numbers.push(b * a);
  } else if (oper == "/") {
    numbers.push(b / a);
  } else if (oper == "^") {
    numbers.push(pow(b, a));
  } else if (oper == "%") {
    numbers.push(fmod(b, a));
  }
  function.pop();
}

int Model::CalculateBrackets(int last) {
  while (function.top() != "(") {
    if (!function.top().find_first_of("sctal~")) {
      CalculateFunctions(function.top());
    } else {
      CalculateOperators(function.top());
    }
  }
  if (function.top() == "(") function.pop();
  if (!function.empty()) {
    last = CheckPriority(function.top());
  } else {
    last = -1;
  }
  return last;
}

int Model::CalculateExpression(int last, int current) {
  while (last >= current) {
    if (!function.top().find_first_of("sctal~")) {
      CalculateFunctions(function.top());
    } else {
      CalculateOperators(function.top());
    }
    if (!function.empty()) {
      last = CheckPriority(function.top());
    } else {
      last = -1;
    }
  }
  return last;
}

int Model::CheckPriority(const std::string& oper) {
  if (!oper.find_first_of("-+")) {
    return 2;
  } else if (!oper.find_first_of("*/%")) {
    return 4;
  } else if (oper == "^") {
    return 5;
  } else if (!oper.find_first_of("sctal")) {
    return 3;
  } else if (oper == "~") {
    return 6;
  }
  return 0;
}

void Model::setStr(const std::string& string) { this->str = string; }

void Model::setX(const double& x) { this->x = x; }
