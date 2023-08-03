#include <iostream>

template<typename Derived>
struct Base {
  void print() {
    Derived* derived = static_cast<Derived*>(this);
    derived->print_impl();
  }
};

struct Foo : public Base<Foo> {
  void print_impl() {
    std::cout << "Foo called." << std::endl;
  }
};

struct Bar : public Base<Bar> {
  void print_impl() {
    std::cout << "Bar called." << std::endl;
  }
};

int main() {
  Foo f;
  Bar b;
  f.print();
  b.print();
}
