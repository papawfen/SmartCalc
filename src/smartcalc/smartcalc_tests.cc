#include <gtest/gtest.h>

#include "smartcalc.h"

std::string str1 = "cos(3-3)+2*3";
std::string str2 = "sin(x)";
std::string str3 = "sin(1)/cos(1)*tan(1)-asin(1)+acos(1)";
std::string str4 = "5+2(-3)*1e-3";

TEST(smart_calc, calculate_test) {
  Model calc;
  calc.setStr(str1);
  ASSERT_NEAR(calc.Polka(), 7.0000000, 1e-6);
  calc.setStr(str3);
  ASSERT_NEAR(calc.Polka(), 0.854722, 1e-6);
  calc.setStr(str4);
  ASSERT_NEAR(calc.Polka(), 1.997, 1e-6);
}

TEST(smart_calc, plot_test) {
  Model calc;
  calc.setStr(str2);
  ASSERT_NEAR(calc.Plot(-10, 10).second.at(128), 0.313828, 1e-6);
}
