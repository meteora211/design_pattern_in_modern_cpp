#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <functional>

using namespace std;

struct HotDrink {
  virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink {
  void prepare(int volume) override {
    std::cout << "make volume " << volume << " of tea" << std::endl;
  }
};

struct Coffee : HotDrink {
  void prepare(int volume) override {
    std::cout << "make volume " << volume << " of coffee" << std::endl;
  }
};

class HotDrinkFactory {
public:
  virtual unique_ptr<HotDrink> make() const = 0;
};

class CoffeeFactory : public HotDrinkFactory {
public:
  unique_ptr<HotDrink> make() const override {
    return make_unique<Coffee>();
  }
};

class TeaFactory : public HotDrinkFactory {
public:
  unique_ptr<HotDrink> make() const override {
    return make_unique<Tea>();
  }
};

class DrinkFactory {
public:
  DrinkFactory() {
    hot_factories["coffee"] = make_unique<CoffeeFactory>();
    hot_factories["tea"] = make_unique<TeaFactory>();
  }

  unique_ptr<HotDrink> make_drink(const string& name) {
    auto drink = hot_factories[name]->make();
    drink->prepare(100);
    return drink;
  }
private:
  map<string, unique_ptr<HotDrinkFactory>> hot_factories;
};

class DrinkFunctionalFactory {
public:
  DrinkFunctionalFactory() {
    hot_factories["tea"] = [](){
      auto drink = make_unique<Tea>();
      drink->prepare(100);
      return drink;
    };
    hot_factories["coffee"] = [](){
      auto drink = make_unique<Coffee>();
      drink->prepare(100);
      return drink;
    };
  }

  unique_ptr<HotDrink> make_drink(const string& name) {
    return hot_factories[name]();
  }
private:
  map<string, function<unique_ptr<HotDrink>()>> hot_factories;
};

int main() {
  auto tea = DrinkFactory().make_drink("tea");
  auto coffee = DrinkFunctionalFactory().make_drink("coffee");
}
