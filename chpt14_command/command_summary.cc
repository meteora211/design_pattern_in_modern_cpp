#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Reciever {
public:
  void operation_a(string a) {
    cout << "operation: a: " << a << endl;
  }
  void operation_b(string b) {
    cout << "operation: b: " << b << endl;
  }
};

class Command {
public:
  virtual ~Command() = default;
  virtual void execute() = 0;
};

class ConcreteCommand : public Command {
public:
  ConcreteCommand(shared_ptr<Reciever> r, string a, string b)
      : reciever(r), arg_a(a), arg_b(b) {}

  void execute() override {
    cout << "concrete command executing" << endl;
    reciever->operation_a(arg_a);
    reciever->operation_b(arg_b);
  }

private:
  shared_ptr<Reciever> reciever;
  string arg_a;
  string arg_b;
};

class Invoker {
public:
  void set_on_start(shared_ptr<Command> c) {
    on_start = c;
  }
  void set_on_finish(shared_ptr<Command> c) {
    on_finish = c;
  }
  void execute_command() {
    if (on_start) {
      on_start->execute();
    }
    cout << "Invoker execte command" << endl;
    if (on_finish) {
      on_finish->execute();
    }
  }
private:
  shared_ptr<Command> on_start;
  shared_ptr<Command> on_finish;
};

int main() {
  auto reciever = make_shared<Reciever>();
  auto invoker = make_shared<Invoker>();
  invoker->set_on_start(make_shared<ConcreteCommand>(reciever, "start", "args"));
  invoker->set_on_finish(make_shared<ConcreteCommand>(reciever, "finish", "args"));
  invoker->execute_command();
}
