#include <iostream>
#include <memory>
#include <string>

using namespace std;

class subsystem1 {
public:
  string operationA() { return "subsystem1: ready.\n"; }
  string operationZ() { return "subsystem1: go.\n"; }
};

class subsystem2 {
public:
  string operation1() { return "subsystem2: get ready.\n"; }
  string operationN() { return "subsystem2: fire.\n"; }
};

class Facade {
public:
  Facade(shared_ptr<subsystem1> sub1, shared_ptr<subsystem2> sub2)
      : subsystem1_{sub1}, subsystem2_{sub2} {}
  string operation() {
    string result;
    result += subsystem1_->operationA();
    result += subsystem1_->operationZ();
    result += subsystem2_->operation1();
    result += subsystem2_->operationN();
    return result;
  }

protected:
  shared_ptr<subsystem1> subsystem1_;
  shared_ptr<subsystem2> subsystem2_;
};

int main() {
  auto sub1 = make_shared<subsystem1>();
  auto sub2 = make_shared<subsystem2>();
  auto f = make_shared<Facade>(sub1, sub2);
  cout << f->operation() << endl;
}
