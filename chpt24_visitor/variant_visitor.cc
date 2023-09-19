#include <iostream>
#include <variant>
#include <vector>

using namespace std;

class Circle {};
class Rectangle {};

void draw(const Circle &) { cout << "draw circle" << endl; }

void draw(const Rectangle &) { cout << "draw rectangle" << endl; }

using Shape = variant<Circle, Rectangle>;

class ConcreteComponentA {
public:
  void special_method_a() { cout << "calling special_method_a" << endl; }
};

class ConcreteComponentB {
public:
  void special_method_b() { cout << "calling special_method_b" << endl; }
};

using Component = variant<ConcreteComponentA, ConcreteComponentB>;

int main() {
  // shape with unified api
  Shape shape = Circle();
  visit([](auto &arg) { return draw(arg); }, shape);

  // general case from visitor_summary
  ConcreteComponentA a;
  ConcreteComponentB b;
  vector<Component> components{a, b};
  for (Component &component : components) {
    visit(
        [](auto &arg) {
          using T = decay_t<decltype(arg)>;
          if constexpr (is_same_v<T, ConcreteComponentA>) {
            arg.special_method_a();
          } else {
            arg.special_method_b();
          }
        },
        component);
  }
}
