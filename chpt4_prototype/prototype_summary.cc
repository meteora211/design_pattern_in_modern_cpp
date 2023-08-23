#include <iostream>
#include <string>
#include <memory>
#include <concepts>
#include <map>
using namespace std;

// XXX: [interface] normal implementation with a interface class
// class Prototype {
//   virtual unique_ptr<Prototype> clone();
// };

// XXX: [interface] try c++20 concept 
// REFERENCE: https://www.reachablecode.com/2019/06/09/concept-based-interfaces/
template <typename T>
concept Prototype = requires(T t) {
  // XXX: [concepts] cppreference: { expression } noexcept(optional) return-type-requirement (optional)
  // the return-type-requirement should be an constraint
  {t.clone()} -> std::convertible_to<unique_ptr<T>>;
};

template<Prototype P>
class PrototypeRegistry {
public:
  static shared_ptr<P> get(string name) {
    return instance().items[name];
  }
  static void set(string name, shared_ptr<P> proto) {
    instance().items[name] = proto;
  }
  static PrototypeRegistry<P>& instance() {
    static PrototypeRegistry<P> singleton;
    return singleton;
  }
private:
  map<string, shared_ptr<P>> items;
  PrototypeRegistry() = default;
};

// XXX: [interface] require clause not support following form:
// class Shape requires Prototype
class Shape {
public:
  virtual unique_ptr<Shape> clone() {
    return make_unique<Shape>(x,y);
  }
  Shape(float x, float y) : x{x}, y{y} {
    // XXX: [interface] use static_assert to do the above requires trick
    static_assert(Prototype<Shape>);
  }
  virtual ~Shape() {}
  virtual void print() const {
    cout << "x: " << x << " y: " << y << endl;
  }
private:
  float x, y;
};

class Rectangle : public Shape {
public:
  unique_ptr<Shape> clone() override {
    return make_unique<Rectangle>(height, width);
  }
  Rectangle(float height, float width) : Shape{height, width}, height{height}, width{width} {}
  void print() const override {
    cout << "width: " << width << " height: " << height << endl;
  }
private:
  float height, width;
};


int main() {
  auto r = make_unique<Rectangle>(1,2);
  auto clone_r = r->clone();
  clone_r->print();

  PrototypeRegistry<Shape>::instance().set("rectangle", make_shared<Rectangle>(3,2));
  PrototypeRegistry<Shape>::instance().get("rectangle")->clone()->print();
}
