#pragma once
#include <iostream>
#include <string>

using namespace std;

class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

class Person {
  // address
  std::string street_address, post_code, city;

  // employment
  std::string company_name, position;
  int annual_income = 0;

public:
  static PersonBuilder create();
  friend class PersonAddressBuilder;
  friend class PersonJobBuilder;
  friend class PersonBuilder;
  friend std::ostream &operator<<(std::ostream &os, const Person &obj) {
    return os << "street_address: " << obj.street_address
              << " post_code: " << obj.post_code << " city: " << obj.city
              << " company_name: " << obj.company_name
              << " position: " << obj.position
              << " annual_income: " << obj.annual_income;
  }
};

class PersonBuilderBase {
protected:
  Person &person;
  explicit PersonBuilderBase(Person &person) : person{person} {}

public:
  operator Person() { return std::move(person); }

  PersonAddressBuilder lives() const;
  PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase {
  Person p; // object being built
public:
  PersonBuilder() : PersonBuilderBase{p} {}
};

class PersonAddressBuilder : public PersonBuilderBase {
  typedef PersonAddressBuilder self;

public:
  explicit PersonAddressBuilder(Person &person) : PersonBuilderBase{person} {}

  self &at(std::string street_address) {
    person.street_address = street_address;
    return *this;
  }
  self &with_postcode(std::string post_code) {
    person.post_code = post_code;
    return *this;
  }
  self &in(std::string city) {
    person.city = city;
    return *this;
  }
};

class PersonJobBuilder : public PersonBuilderBase {
  typedef PersonJobBuilder self;

public:
  explicit PersonJobBuilder(Person &person) : PersonBuilderBase{person} {}

  self &at(std::string company_name) {
    person.company_name = company_name;
    return *this;
  }
  self &earns(int annual_income) {
    person.annual_income = annual_income;
    return *this;
  }
  self &as(std::string position) {
    person.position = position;
    return *this;
  }
};
