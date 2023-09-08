#include <iostream>
#include <memory>
#include <string>
#include <list>

using namespace std;

class IObserver {
public:
  virtual ~IObserver() = default;
  virtual void update(const string& message) = 0;
};

class ISubject {
public:
  virtual ~ISubject() = default;
  virtual void detach(IObserver*) = 0;
  virtual void attach(IObserver*) = 0;
  virtual void notify(const string& msg) = 0;
};

class ConcreteObserver : public IObserver {
public:
  ConcreteObserver(shared_ptr<ISubject> subject) : subject(subject) {
    subject->attach(this);
  }
  void update(const string& msg) override {
    message = msg;
  }
  void unsubcribe() {
    subject->detach(this);
  }

  void execute() {
    cout << message << endl;
  }
private:
  shared_ptr<ISubject> subject;
  string message;
};

class ConcreteSubject : public ISubject {
public:
  ConcreteSubject() {}
  void detach(IObserver* ob) override {
    ob_list.remove(ob);
  }
  void attach(IObserver* ob) override {
    ob_list.push_back(ob);
  }
  void notify(const string& msg) override {
    for (auto ob : ob_list) {
      ob->update(msg);
    }
  }
private:
  list<IObserver*> ob_list;
};

int main() {
  auto subject = make_shared<ConcreteSubject>();
  auto ob1 = make_shared<ConcreteObserver>(subject);
  auto ob2 = make_shared<ConcreteObserver>(subject);
  subject->notify("ready");
  ob1->execute(); ob2->execute();
}
