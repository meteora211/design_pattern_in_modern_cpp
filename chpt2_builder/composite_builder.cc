#include "composite_builder.h"
using namespace std;

class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;

PersonBuilder Person::create() { return PersonBuilder{}; }

PersonAddressBuilder PersonBuilderBase::lives() const {
  return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works() const {
  return PersonJobBuilder(person);
}

int main() {
  // XXX: crtp can be used to make fluent API works when builder inheritance occurs.
  Person p = Person::create()
                 .lives()
                 .at("street")
                 .with_postcode("404")
                 .in("LA")
                 .works()
                 .at("soft")
                 .as("engineer")
                 .earns(-1);
  std::cout << p << std::endl;
}
