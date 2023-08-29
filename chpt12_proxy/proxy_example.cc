#include <iostream>
#include <string>
#include <vector>
// #include <concepts>

using namespace std;

// void dump_type (auto) requires false {}

// Property Proxy
template<typename T>
class Property {
public:
  Property(const T value) {
    *this = value;
  }

  T operator= (T value) {
    cout << "setter called: " << value << endl;
    return value_ = value;
  }

  operator T() {
    cout << "getter called: " << value_ << endl;
    return value_;
  }

private:
  T value_;
};

struct Creature {
  Property<int> strength{10};
};

// Value Proxy
template<typename T>
class Value {
public:
  virtual operator T() const = 0;
};

template <typename T>
class Const : Value<T> {
public:
  Const(T value) : value_{value} {}
  Const() : value_{} {}
  operator T() const override {
    return value_;
  }
private:
  const T value_;
};

template<typename T>
class OneOf : Value<T> {
public:
  OneOf() : values_{} {}
  OneOf(std::initializer_list<T> list) : values_{list} {}
  OneOf(const vector<T>& v) : values_{v} {}

  operator T() const override {
    return values_[rand() % values_.size()];
  }

private:
  vector<T> values_;
};

int main() {
  auto c = Creature();
  c.strength = 15;
  int x = c.strength;
  // dump_type(x);

  Const<int> const_int{42};
  cout << const_int / 2 << endl;
  OneOf<int> one_value{1, 2, 3};
  cout << one_value << endl;
}
