#ifndef BACK_TOKENS_H
#define BACK_TOKENS_H

#include <string>

class Tokens {
 public:
  explicit Tokens(const std::string &number) : function(number), priority(-1) {}

  Tokens(const std::string &function,const int &priority) : function(function), priority(priority) {}

  const std::string &getFunction() const;

  int getPriority() const;

 private:
  std::string function;
  int priority;
};

#endif  // BACK_TOKENS_H
