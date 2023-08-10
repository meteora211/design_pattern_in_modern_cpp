#include <iostream>
#include <string>
using namespace std;

template <typename Derived> struct Base {
  void print() {
    Derived *derived = static_cast<Derived *>(this);
    derived->print_impl();
  }
};

struct Foo : public Base<Foo> {
  void print_impl() { std::cout << "Foo called." << std::endl; }
};

struct Bar : public Base<Bar> {
  void print_impl() { std::cout << "Bar called." << std::endl; }
};

template <typename Printable> class RepeatPrintable {
public:
  void repeat(int n) const {
    for (auto i = 0; i < n; ++i) {
      static_cast<const Printable *>(this)->print();
    }
  }
};

class Name : public RepeatPrintable<Name> {
public:
  Name(std::string firstName, std::string lastName)
      : firstName_(std::move(firstName)), lastName_(std::move(lastName)) {}
  void print() const {
    std::cout << firstName_ << ", " << lastName_ << std::endl;
  }

private:
  std::string firstName_;
  std::string lastName_;
};

int main() {
  Foo f;
  Bar b;
  f.print();
  b.print();

  Name czr("Zhaorui", "Chen");
  czr.repeat(5);
}
