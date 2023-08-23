#pragma once
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class PersonImpl{
public:
  PersonImpl() = default;
  ~PersonImpl() = default;
  void greet() const {
    cout << "hello" << endl;
  }
  string name() const {
    return name_;
  }
  void set_name(const string& name) {
    name_ = name;
  }

private:
  string name_;
};
