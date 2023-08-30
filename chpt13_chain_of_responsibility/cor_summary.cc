#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Handler {
public:
  virtual shared_ptr<Handler> set_next(shared_ptr<Handler>) = 0;
  virtual string handle(string request) = 0;
};

class AbstractHandle : public Handler {
public:
  AbstractHandle() : h_(nullptr) {}
  AbstractHandle(shared_ptr<Handler> h) : h_(h) {}
  virtual ~AbstractHandle() {}
  shared_ptr<Handler> set_next(shared_ptr<Handler> h) override {
    h_ = h;
    return h_;
  }
  virtual string handle(string request) override {
    if (h_) {
      return h_->handle(request);
    }
    return {};
  }
private:
  shared_ptr<Handler> h_;
};

class SquirrelHandler : public AbstractHandle {
public:
  string handle(string request) override {
    if (request == "Nut") {
      return "Squirrel: eat Nut.";
    } else {
      return AbstractHandle::handle(request);
    }
  }
};

class DogHandler : public AbstractHandle {
public:
  string handle(string request) override {
    if (request == "Meat") {
      return "Dog: eat Meat.";
    } else {
      return AbstractHandle::handle(request);
    }
  }
};

int main() {
  auto handler = make_shared<AbstractHandle>();
  handler->set_next(make_shared<DogHandler>())->set_next(make_shared<SquirrelHandler>());
  for (auto&& request : {"Nut", "Meat", "Apple"}) {
    auto response = handler->handle(request);
    if (response.empty()) {
      cout << request << " left untouched." << endl;
    } else {
      cout << response << endl;
    }
  }
}
