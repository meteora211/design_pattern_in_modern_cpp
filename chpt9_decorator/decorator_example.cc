#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Shape {
public:
  Shape() = default;
  virtual ~Shape() = default;
  virtual string str() const = 0;
};

class Circle : public Shape {
public:
  explicit Circle(float r) : r_{r} {}
  string str() const override { return "Circle with r: " + to_string(r_); }

private:
  float r_;
};

class ColorWrapper : public Shape {
public:
  ColorWrapper(shared_ptr<Shape> shape, const string &color)
      : shape_{shape}, color_{color} {}
  virtual string str() const override {
    return shape_->str() + " Colored with: " + color_;
  }

private:
  shared_ptr<Shape> shape_;
  string color_;
};

class TransparentWrapper : public Shape {
public:
  TransparentWrapper(shared_ptr<Shape> shape, int trans)
      : shape_{shape}, trans_{trans} {}
  virtual string str() const override {
    return shape_->str() + " Transparented with: " + to_string(trans_);
  }

private:
  shared_ptr<Shape> shape_;
  int trans_;
};

void print_shape(shared_ptr<Shape> s) { cout << s->str() << endl; }

// STATIC decorator
template <typename T> class StaticColorWrapper : public T {
public:
  StaticColorWrapper(shared_ptr<T> shape, const string &color)
      : shape_{shape}, color_{color} {
    static_assert(is_base_of_v<Shape, T>);
  }
  // XXX: T(std::forward<Args>(args)...) is to initializer the BASE class T. see:
  // https://stackoverflow.com/questions/23647409/error-base-class-constructor-must-explicitly-initialize-parent-class-construct
  template <typename... Args>
  StaticColorWrapper(const string &color, Args... args)
      : T(std::forward<Args>(args)...),
        shape_(make_shared<T>(std::forward<Args>(args)...)), color_{color} {
    static_assert(is_base_of_v<Shape, T>);
  }
  virtual string str() const override {
    return shape_->str() + " Colored with: " + color_;
  }

private:
  shared_ptr<T> shape_;
  string color_;
};
template <typename T> class StaticTransparentWrapper : public T {
public:
  StaticTransparentWrapper(shared_ptr<T> shape, int trans)
      : shape_{shape}, trans_{trans} {
    static_assert(is_base_of_v<Shape, T>);
  }
  template <typename... Args>
  StaticTransparentWrapper(int trans, Args... args)
      : T(std::forward<Args>(args)...),
        shape_(make_shared<T>(std::forward<Args>(args)...)), trans_{trans} {
    static_assert(is_base_of_v<Shape, T>);
  }
  virtual string str() const override {
    return shape_->str() + " Transparented with: " + to_string(trans_);
  }

private:
  shared_ptr<T> shape_;
  int trans_;
};

int main() {
  auto circle = make_shared<Circle>(10);
  auto wrap_with_color = make_shared<ColorWrapper>(circle, "blue");
  auto wrap_with_trans = make_shared<TransparentWrapper>(wrap_with_color, 3);
  print_shape(wrap_with_trans);

  auto c = make_shared<StaticColorWrapper<StaticTransparentWrapper<Circle>>>(
      "red", 5, 6);
  // auto c = make_shared<StaticTransparentWrapper<Circle>>(5, 6.0);
  // StaticTransparentWrapper<Circle> c{5, 6.0};
  print_shape(c);
}
