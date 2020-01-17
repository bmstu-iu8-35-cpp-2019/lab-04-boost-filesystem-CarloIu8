// Copyright 2018 Your Name <your_email>

#include <header.hpp>

namespace fs = boost::filesystem;

operation::operation(std::string s, int num, int da) {
  broker = s;
  number = num;
  data = da;
}
bool operation::operator>(const operation& a) const {
  return (a.number > number);
}
bool operation::operator<(const operation& a) const {
  return (a.number < number);
}
std::string operation::get_B() const { return broker; }
int operation::get_D() const { return data; }
int operation::get_N() const { return number; }
