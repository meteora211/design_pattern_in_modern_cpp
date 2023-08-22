#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Address {
public:
  Address(const string &street, const string &city, const int suite)
      : street{street}, city{city}, suite{suite} {}
  Address(const Address &other)
      : street{other.street}, city{other.city}, suite{other.suite} {}
  Address &operator=(const Address &other) {
    if (this == &other) {
      return *this;
    }
    street = other.street;
    city = other.city;
    suite = other.suite;
    return *this;
  }
  string street, city;
  int suite;
};

class ExtendAddress : public Address {
public:
  ExtendAddress(const string &street, const string &city, const int suite, const string& country)
      : Address{street, city, suite}, country{country} {}
  ExtendAddress(const ExtendAddress &other)
      : Address(other), country{other.country} {}
  ExtendAddress &operator=(const ExtendAddress &other) {
    if (this == &other) {
      return *this;
    }
    Address::operator=(other);
    country = other.country;
    return *this;
  }
  string country;
};

class Contact {
public:
  Contact(string name, unique_ptr<Address> address)
      : name(name), address(std::move(address)) {}
  Contact(const Contact &other)
      : name{other.name}, address(make_unique<Address>(*other.address)) {}
  Contact &operator=(const Contact &other) {
    if (this == &other) {
      return *this;
    }
    name = other.name;
    address = make_unique<Address>(*other.address);
    return *this;
  }
  ~Contact() {
    address.reset();
  }
  string name;
  unique_ptr<Address> address;
};

ostream &operator<<(ostream &os, const Contact &obj) {
  return os << "name: " << obj.name
            << " street: " << obj.address->street
            << " city: " << obj.address->city
            << " suite: " << obj.address->suite;
}

// Prototype Factory
class EmployeeFactory {
  static Contact main;
  static Contact aux;

  static unique_ptr<Contact> NewEmployee(
      const string& name, int suite, const Contact& proto) {
    auto result = make_unique<Contact>(proto);
    result->name = name;
    result->address->suite = suite;
    return result;
  }
public:
  static unique_ptr<Contact> NewMainOfficeEmployee(const string& name, int suite) {
    return NewEmployee(name, suite, main);
  }
  static unique_ptr<Contact> NewAuxOfficeEmployee(const string& name, int suite) {
    return NewEmployee(name, suite, main);
  }
};

Contact EmployeeFactory::main{"", make_unique<Address>("123 East Dr", "London", 0)};
Contact EmployeeFactory::aux{"", make_unique<Address>("321 East Dr", "London", 0)};

int main() {
  // XXX: prototype
  Contact worker{"", make_unique<Address>("123 East Dr", "London", 0)};
  auto john = worker;
  john.name = "John";
  john.address->suite = 10;
  cout << john << endl;

  auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane Doe", 125);
  cout << *jane << endl;
}
