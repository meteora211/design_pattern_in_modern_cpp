#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

struct state {
  int count;
  string value;
};

class Originator {
public:
  class Memento {
  public:
    Memento(const state& s) :s_{make_shared<state>(s)} {}
    shared_ptr<state> get_state() {
      return s_;
    }
  private:
    shared_ptr<state> s_;
  };

  Originator() : s_(make_shared<state>(0, "0")) {}
  shared_ptr<Memento> save() {
    return make_shared<Memento>(*s_);
  }
  void restore(shared_ptr<Memento> m) {
    set_state(m->get_state());
  }
  void set_state(shared_ptr<state> s) {
    s_ = s;
  }
  void execute() {
    ++(s_->count);
    s_->value += to_string(s_->count);
  }
  void show_state() {
    cout << s_->count << " " << s_->value << endl;
  }
private:
  shared_ptr<state> s_;
};

class Caretaker {
public:
  Caretaker(shared_ptr<Originator> originator) : originator(originator) {}
  void backup() {
    auto m = originator->save();
    history.push_back(m);
  }
  void restore() {
    auto m = history.back();
    originator->restore(m);
    history.pop_back();
  }
  void show_history() {
    for (auto m : history) {
      auto s = m->get_state();
      cout << s->count << " " << s->value << endl;
    }
  }
private:
  shared_ptr<Originator> originator;
  vector<shared_ptr<Originator::Memento>> history;
};

int main() {
  auto originator = make_shared<Originator>();
  auto caretaker = make_shared<Caretaker>(originator);
  for (int i = 0; i < 10; ++i) {
    caretaker->backup();
    originator->execute();
  }
  caretaker->show_history();
  for (int i = 0; i < 10; ++i) {
    caretaker->restore();
    originator->show_state();
  }
  caretaker->show_history();
}
