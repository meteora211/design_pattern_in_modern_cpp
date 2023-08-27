#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Component {
public:
  Component() = default;
  virtual ~Component() = default;
  virtual string operation() const = 0;
};

class ConcreteComponent : public Component {
  string operation() const override {
    return "ConcreteComponent";
  }
};

class BaseDecorator : public Component {
public:
  BaseDecorator(shared_ptr<Component> c) : component_{c} {}
  virtual ~BaseDecorator() = default;
  virtual string operation() const override {
    return component_->operation();
  }

protected:
  shared_ptr<Component> component_;
};

class DecoratorA : public BaseDecorator {
public:
  DecoratorA(shared_ptr<Component> c) : BaseDecorator{c} {}
  virtual string operation() const override {
    return "DecoratorA(" + component_->operation() + ")";
  }
};

void do_operation(shared_ptr<Component> c) {
  cout << c->operation() << endl;
}

int main() {
  auto actual_component = make_shared<ConcreteComponent>();
  auto wrap_component = make_shared<DecoratorA>(actual_component);

  do_operation(actual_component);
  do_operation(wrap_component);
}
