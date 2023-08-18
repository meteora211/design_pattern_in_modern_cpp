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

int main() {
  Contact worker{"", make_unique<Address>("123 East Dr", "London", 0)};
  auto john = worker;
  john.name = "John";
  john.address->suite = 10;
  cout << john << endl;
}
