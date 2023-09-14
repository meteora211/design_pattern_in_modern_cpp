#include <iostream>
#include <string>
#include <memory>
#include <string_view>
#include <algorithm>

using namespace std;

class Strategy {
public:
  Strategy() = default;
  virtual ~Strategy() = default;

  virtual string algo(string_view data) = 0;
};

class Context {
public:
  Context(unique_ptr<Strategy>&& s={}) : s_(std::move(s)) {}

  void execute() {
    if (s_) {
      cout << s_->algo("bacfe") << endl;
    } else {
      cout << "strategy not set";
    }
  }

  void set_strategy(unique_ptr<Strategy>&& s) {
    s_ = std::move(s);
  }

private:
  unique_ptr<Strategy> s_;
};

class ConcreteStrategyA : public Strategy {
public:
  ConcreteStrategyA() = default;
  string algo(string_view data) override {
    string result{data};
    cout << "using algo A to sort " << data << endl;
    sort(begin(result), end(result));
    return result;
  }
};

class ConcreteStrategyB : public Strategy {
public:
  ConcreteStrategyB() = default;
  string algo(string_view data) override {
    string result{data};
    cout << "using algo B to sort " << data << endl;
    sort(begin(result), end(result), greater<>());
    return result;
  }
};

int main() {
  auto sa = make_unique<ConcreteStrategyA>();
  auto sb = make_unique<ConcreteStrategyB>();
  Context c(std::move(sa));
  c.execute();
  c.set_strategy(std::move(sb));
  c.execute();
}

