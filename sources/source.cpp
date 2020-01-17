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
        for (size_t z = 8; z < 16; z++) {
          if (s[z] >= 48 && s[z] <= 57) {
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
                arr[oper]++;
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

void how_many_operations(std::map<operation, int>& arr) {
  for (std::map<operation, int>::iterator it = arr.begin(); it != arr.end();
       it++) {
    std::cout << "Broker:" << (it->first).get_B()
              << " account:" << it->first.get_N() << " Files:" << it->second
              << std::endl;
  }
}

void otvet(std::string file_path) {
  boost::filesystem::path a(file_path);
  std::map<operation, int> arr;
  search(a, a, arr);
  how_many_operations(arr);
}
