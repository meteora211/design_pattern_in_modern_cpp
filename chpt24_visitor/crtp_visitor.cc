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

template<typename Derived>
class APIBase : public Component, public enable_shared_from_this<APIBase<Derived>> {
  void accept(Visitor& v) override;
};


class ConcreteComponentA : public APIBase<ConcreteComponentA> {
public:
  void special_method_a () {
    cout << "calling special_method_a" << endl;
  }
};

class ConcreteComponentB : public APIBase<ConcreteComponentB> {
public:
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

template<typename Derived>
void APIBase<Derived>::accept(Visitor& v) {
  v.visit(*static_cast<Derived*>(this));
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

