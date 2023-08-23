#pragma once
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class PersonImpl;
class Person {
public:
  Person();
  ~Person();
  void greet() const;
  string name() const;
  void set_name(const string&);

private:
  unique_ptr<PersonImpl> impl;
};
