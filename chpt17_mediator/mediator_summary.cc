#include <iostream>
#include <memory>
#include <string>

using namespace std;

class BaseComponet;
class Mediator {
public:
  virtual void notify(BaseComponet* sender, string event) = 0;
};

class BaseComponet {
protected:
  Mediator* m_;
public:
  BaseComponet(Mediator* m = nullptr) : m_(m) {}
  void set_mediator(Mediator* m) {
    m_ = m;
  }
};

class Component1 : public BaseComponet {
public:
  void execute_a() {
    cout << "execute a" << endl;
    m_->notify(this, "A");
  }
  void execute_b() {
    cout << "execute b" << endl;
    m_->notify(this, "B");
  }
};

class Component2 : public BaseComponet {
public:
  void execute_c() {
    cout << "execute c" << endl;
    m_->notify(this, "C");
  }
  void execute_d() {
    cout << "execute d" << endl;
    m_->notify(this, "D");
  }
};

class ConcreteMediator : public Mediator {
public:
  ConcreteMediator(shared_ptr<Component1> c1, shared_ptr<Component2> c2) :
    c1_(c1), c2_(c2) {
    c1_->set_mediator(this);
    c2_->set_mediator(this);
  }
  void notify(BaseComponet* sender, string event) {
    if (event == "A") {
      cout << "mediator notify C" << endl;
      c2_->execute_c();
    } else if (event == "B") {
      cout << "mediator notify D" << endl;
      c2_->execute_d();
    }
  }
private:
  shared_ptr<Component1> c1_;
  shared_ptr<Component2> c2_;
};

int main() {
  auto c1 = make_shared<Component1>();
  auto c2 = make_shared<Component2>();
  auto mediator = make_shared<ConcreteMediator>(c1, c2);
  c1->execute_a();
  c1->execute_b();
}
