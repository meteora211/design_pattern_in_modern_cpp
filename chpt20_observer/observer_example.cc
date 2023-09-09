#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

template <typename T> struct Observer {
  virtual void field_change(T &, const string &) = 0;
};

template <typename T> class Observable {
public:
  void attach(Observer<T> *ob) {
    scoped_lock lock{m};
    observers.push_back(ob);
  };
  void detach(Observer<T> *ob) {
    scoped_lock lock{m};
    observers.remove(ob);
  }
  void notify(T &source, const string &name) {
    scoped_lock lock{m};
    for (auto ob : observers) {
      ob->field_change(source, name);
    }
  };

private:
  list<Observer<T> *> observers;
  mutex m;
};

class Person : public Observable<Person> {
public:
  Person(const string &name, int age) : name(name), age(age) {}
  int get_age() const { return age; }
  string get_name() const { return name; }
  void set_age(const int value) {
    bool vote_state = can_vote();
    age = value;
    notify(*this, "age");
    if (vote_state != can_vote()) {
      notify(*this, "can_vote");
    }
  }
  bool can_vote() const { return age > 18; }

private:
  string name;
  int age;
};

class PersonObserver : public Observer<Person> {
public:
  PersonObserver(shared_ptr<Observable<Person>> p) : p(p) { p->attach(this); }
  ~PersonObserver() { p->detach(this); }
  void field_change(Person &p, const string &name) override {
    // XXX: need reflection here
    cout << p.get_name() << " field: " << name << " changes to " << p.get_age()
         << endl;
  }

private:
  shared_ptr<Observable<Person>> p;
};

int main() {
  auto p = make_shared<Person>("john", 18);
  vector<shared_ptr<PersonObserver>> ob_cache;
  mutex m;
  auto create_ob = [&](){
    auto po = make_shared<PersonObserver>(p);
    {
      scoped_lock lock{m};
      ob_cache.push_back(po);
    }
  };
  vector<thread> threads;
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(create_ob);
  }
  for (auto& t : threads) {
    t.join();
  }
  // auto po1 = make_shared<PersonObserver>(p);
  // auto po2 = make_shared<PersonObserver>(p);
  p->set_age(19);
}
