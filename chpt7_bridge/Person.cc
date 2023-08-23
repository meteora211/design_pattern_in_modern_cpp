#include "Person.h"
#include "PersonImpl.h"

Person::Person() : impl{make_unique<PersonImpl>()} {}

Person::~Person() = default;

void Person::greet() const {
  impl->greet();
}

string Person::name() const {
  return impl->name();
}

void Person::set_name(const string& name) {
  impl->set_name(name);
}

int main() {
  auto p = Person();
  p.set_name("John");
  cout << p.name() << " says: ";
  p.greet();
}
