#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Visitor;

class Component {
public:
  virtual ~Component() {}
  virtual void accept(Visitor& v) = 0;
};

class ConcreteComponentA : public Component {
public:
  void accept(Visitor& v) override;
  void special_method_a () {
    cout << "calling special_method_a" << endl;
  }
};

class ConcreteComponentB : public Component {
public:
  void accept(Visitor& v) override;
  void special_method_b () {
    cout << "calling special_method_b" << endl;
  }
};

class Visitor {
public:
  void visit(ConcreteComponentA& component) {
    component.special_method_a();
  }
  void visit(ConcreteComponentB& component) {
    component.special_method_b();
  }
};

void ConcreteComponentA::accept(Visitor& v) {
  v.visit(*this);
}
void ConcreteComponentB::accept(Visitor& v) {
  v.visit(*this);
}

int main() {
  Visitor v;
  ConcreteComponentA a;
  ConcreteComponentB b;
  vector<Component*> components{&a, &b};
  for (Component* component : components) {
    component->accept(v);
  }
}

