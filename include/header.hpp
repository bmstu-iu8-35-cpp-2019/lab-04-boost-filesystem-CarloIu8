// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <any>
#include <boost/filesystem.hpp>
#include <iostream>
#include <map>
#include <string>

namespace fs = boost::filesystem;

class operation {
 public:
  operation(std::string s, int num, int da);
  bool operator>(const operation& a) const;
  bool operator<(const operation& a) const;
  std::string get_B() const;
  int get_D() const;
  int get_N() const;

 private:
  std::string broker;
  int data;
  int number;
};


#endif  // INCLUDE_HEADER_HPP_
