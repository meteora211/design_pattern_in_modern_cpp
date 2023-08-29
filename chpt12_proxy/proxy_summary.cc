#include <iostream>
#include <memory>

using namespace std;

class Subject {
public:
  virtual void request() = 0;
  Subject() = default;
  virtual ~Subject() = default;
};

class RealSubject : public Subject {
public:
  void request() override {
    cout << "real subject" << endl;
  }
};

class Proxy : public Subject {
public:
  Proxy() : subject_(nullptr) {}
  Proxy(shared_ptr<Subject> rs) : subject_(rs) {}
  void request() override {
    if (check_access()) {
      subject_->request();
      cout << "Proxy: handling request" << endl;
    } else {
      subject_ = make_shared<RealSubject>();
      subject_->request();
      cout << "Proxy: creating subject and handling request" << endl;
    }
  }

  bool check_access() {
    cout << "Proxy: check access" << endl;
    return subject_ != nullptr;
  }

private:
  shared_ptr<Subject> subject_;
};

int main() {
  Proxy().request();
  Proxy(make_shared<RealSubject>()).request();
}
