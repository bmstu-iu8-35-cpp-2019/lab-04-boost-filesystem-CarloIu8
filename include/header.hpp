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
  operation(std::string s, int num, int da) {
    broker = s;
    number = num;
    data = da;
  }
  bool operator>(const operation& a) const { return (a.number > number); }
  bool operator<(const operation& a) const { return (a.number < number); }
  std::string get_B() const { return broker; }
  int get_D() const { return data; }
  int get_N() const { return number; }

 private:
  std::string broker;
  int data;
  int number;
};

void search(const fs::path& file_path, fs::path& directory,
            std::map<operation, int>& arr) {
  for (const boost::filesystem::directory_entry& i :
       boost::filesystem::directory_iterator{file_path}) {
    std::map<int, int> object;
    if (fs::is_regular_file(i)) {
      std::string s = i.path().filename().string();
      std::string x;
      if (s.substr(0, 8) == "balance_") {
        bool flag1 = true;
        for (size_t i = 8; i < 16; i++) {
          if (s[i] >= 48 && s[i] <= 57) {
            continue;
          } else {
            flag1 = false;
          }
        }
        if (flag1) {
          if (s[16] == '_') {
            bool flag2 = true;
            for (size_t m = 8; m < 16; m++) {
              if (s[m] >= 48 && s[m] <= 57) {
                continue;
              } else {
                flag2 = false;
              }
            }
            if (flag2) {
              if (s.substr(25, 4) == ".txt") {
                if (stoi(s.substr(17, 8)) >= object[stoi(s.substr(8, 8))])
                  object[stoi(s.substr(8, 8))] = stoi(s.substr(17, 8));
                std::cout << directory.filename().string() << " " << s
                          << std::endl;
                operation oper(directory.filename().string(),
                               stoi(s.substr(8, 8)),
                               object[stoi(s.substr(8, 8))]);
                arr[oper] = arr[oper]++;
              }
            }
          }
        }
      }
    } else {
      directory = i.path();
      search(i.path(), directory, arr);
    }
  }
  return;
}

void how_many_operations(std::map<operation, int> arr) {
  for (std::map<operation, int>::iterator it = arr.begin(); it != arr.end();
       it++) {
    std::cout << "Broker:" << (it->first).get_B()
              << " account:" << it->first.get_N() << " Files:" << it->second
              << std::endl;
  }
}

void otvet() {
  boost::filesystem::path a("misc");
  std::map<operation, int> arr;
  search(a, a, arr);
  how_many_operations(arr);
}
#endif  // INCLUDE_HEADER_HPP_
