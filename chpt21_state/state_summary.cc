#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Context;

class State {
public:
  State() = default;
  virtual ~State() {}
  void set_context(Context* c) {
    context = c;
  }
  virtual void handle1() = 0;
  virtual void handle2() = 0;
  virtual void state() = 0;

protected:
  Context* context;
};

class Context {
public:
  Context(shared_ptr<State> state) : state(state) {
    state->set_context(this);
  }
  void transition_to(shared_ptr<State> s) {
    s = state;
    state->set_context(this);
  }
  void request1() {
    state->handle1();
  }
  void request2() {
    state->handle2();
  }
  void status() {
    state->state();
  }
private:
  shared_ptr<State> state;
};

class ConcreteStateA : public State {
public:
  void handle1() override {
    cout << "keep state a" << endl;
  }
  void handle2() override;
  void state() override {
    cout << "state a" << endl;
  }
};

class ConcreteStateB : public State {
public:
  void handle1() override {
    cout << "switch state a" << endl;
    context->transition_to(make_shared<ConcreteStateA>());
  }
  void handle2() override {
    cout << "keep state b" << endl;
  }
  void state() override {
    cout << "state b" << endl;
  }
};

void ConcreteStateA::handle2() {
  cout << "switch state b" << endl;
  context->transition_to(make_shared<ConcreteStateB>());
}

int main() {
  auto init_state = make_shared<ConcreteStateA>();
  Context c{init_state};
  c.request1();
  c.request2();
  c.status();
}
