#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Creature{
  string name;
  int attack, defense;
};

class CreatureModifier {
public:
  CreatureModifier(shared_ptr<Creature> c) : creature(c) {}
  virtual ~CreatureModifier() = default;
  virtual void handle() {
    if (next) {
      next->handle();
    }
  }
  void add(shared_ptr<CreatureModifier> m) {
    if (next) {
      next->add(m);
    } else {
      next = m;
    }
  }
protected:
  shared_ptr<Creature> creature;
private:
  shared_ptr<CreatureModifier> next;
};

class DoubleAttackModifier : public CreatureModifier {
public:
  DoubleAttackModifier(shared_ptr<Creature> c) : CreatureModifier(c) {}
  void handle() override {
    if (creature) {
      creature->attack *= 2;
    }
    CreatureModifier::handle();
  }
};

class IncreaseDefenseModifier : public CreatureModifier {
public:
  IncreaseDefenseModifier(shared_ptr<Creature> c) : CreatureModifier(c) {}
  void handle() override {
    if (creature) {
      creature->defense += 1;
    }
    CreatureModifier::handle();
  }
};

int main() {
  auto goblin = make_shared<Creature>("Goblin", 1, 1);
  auto root = make_shared<CreatureModifier>(goblin);
  auto da = make_shared<DoubleAttackModifier>(goblin);
  auto id = make_shared<IncreaseDefenseModifier>(goblin);
  root->add(da);
  root->add(id);
  root->handle();
  cout << "attack: " << goblin->attack << " defense: " << goblin->defense << endl;
}
