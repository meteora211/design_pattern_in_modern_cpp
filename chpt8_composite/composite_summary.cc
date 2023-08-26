#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <memory>

using namespace std;

class Componet : public enable_shared_from_this<Componet> {
public:
  Componet() : parent_{nullptr} {}
  virtual ~Componet() {}
  void set_parent(shared_ptr<Componet> parent) {
    parent_ = parent;
  }

  shared_ptr<Componet> get_parent() const {
    return parent_;
  }

  virtual void add(shared_ptr<Componet>) {}
  virtual void remove(shared_ptr<Componet>) {}
  virtual bool is_composite() {
    return false;
  }
  virtual string operation() = 0;
protected:
  shared_ptr<Componet> parent_;
};

class Leaf : public Componet {
public:
  string operation() override {
    return "leaf";
  }
};

class Composite : public Componet {
protected:
  list<shared_ptr<Componet>> children_;

public:
  void add(shared_ptr<Componet> componet) override {
    children_.push_back(componet);
    componet->set_parent(shared_from_this());
  }
  void remove(shared_ptr<Componet> componet) override {
    children_.remove(componet);
    componet->set_parent(nullptr);
  }
  bool is_composite() override {
    return true;
  }
  string operation() override {
    string result;
    for (auto c : children_) {
      if (c == children_.back()) {
        result += c->operation();
      } else {
        result += c->operation() + "+";
      }
    }
    return "Branch(" + result + ")";
  }
};

int main() {
  auto tree = make_shared<Composite>();
  auto branch1 = make_shared<Composite>();

  auto leaf_1 = make_shared<Leaf>();
  auto leaf_2 = make_shared<Leaf>();
  auto leaf_3 = make_shared<Leaf>();
  branch1->add(leaf_1);
  branch1->add(leaf_2);
  auto branch2 = make_shared<Composite>();
  branch2->add(leaf_3);
  tree->add(branch1);
  tree->add(branch2);
  cout << tree->operation() << endl;
}
