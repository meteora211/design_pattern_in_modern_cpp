// Open-Closed Principle
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
  string name;
  Color color;
  Size size;
};

///////////////////////////////////////////////////////////////
//      implementation that breaks Open-Closed Principle     //
///////////////////////////////////////////////////////////////
struct ProductFilter {
  typedef std::vector<Product *> Items;

  Items by_color(Items items, Color color) {
    Items result;
    for (auto *item : items) {
      if (item->color == color) {
        result.push_back(item);
      }
    }
    return result;
  }

  Items by_size(Items items, Size size) {
    Items result;
    for (auto *item : items) {
      if (item->size == size) {
        result.push_back(item);
      }
    }
    return result;
  }

  Items by_color_and_size(Items items, Color color, Size size) {
    Items result;
    for (auto *item : items) {
      if (item->color == color && item->size == size) {
        result.push_back(item);
      }
    }
    return result;
  }
};

///////////////////////////////////////////////////////////////
//      implementation follows Open-Closed Principle         //
///////////////////////////////////////////////////////////////
template <typename T> struct AndSpecification;

template <typename T> struct Specification {
  virtual bool is_satisfied(T *item) const = 0;
  AndSpecification<T> operator&&(const Specification<T> &other) {
    std::cout << "internal && called." << std::endl;
    return {*this, other};
  }
};

template <typename T> struct Filter {
  virtual std::vector<T *> filter(std::vector<T *> items,
                                  const Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product> {
  std::vector<Product *> filter(std::vector<Product *> items,
                                const Specification<Product> &spec) {
    std::vector<Product *> result;
    for (auto *item : items) {
      if (spec.is_satisfied(item)) {
        result.push_back(item);
      }
    }
    return result;
  }
};

template <typename T> struct AndSpecification : Specification<T> {
  AndSpecification(const Specification<T> &first,
                   const Specification<T> &second)
      : first{first}, second{second} {}
  bool is_satisfied(T *item) const override {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
  const Specification<T> &first;
  const Specification<T> &second;
};

template <typename T>
AndSpecification<T> operator&&(const Specification<T> &first,
                               const Specification<T> &second) {
  std::cout << "external && called." << std::endl;
  return {first, second};
}

struct ColorSpecification : Specification<Product> {
  explicit ColorSpecification(const Color c) : color(c) {}
  bool is_satisfied(Product *item) const override {
    return item->color == color;
  }
  Color color;
};

struct SizeSpecification : Specification<Product> {
  explicit SizeSpecification(const Size s) : size(s) {}
  bool is_satisfied(Product *item) const override { return item->size == size; }
  Size size;
};

template <typename T>
void print_helper(std::vector<T *> items, const std::string &filter_name) {
  for (auto *item : items) {
    std::cout << item->name << " is " << filter_name << std::endl;
  }
}

int main() {
  Product apple{.name = "Apple", .color = Color::Green, .size = Size::Small};
  Product tree{.name = "Tree", .color = Color::Green, .size = Size::Large};
  Product house{.name = "House", .color = Color::Blue, .size = Size::Large};

  std::vector<Product *> all{&apple, &tree, &house};
  BetterFilter bf;

  ColorSpecification green(Color::Green);
  SizeSpecification large(Size::Large);
  auto green_things = bf.filter(all, green);
  auto large_things = bf.filter(all, large);
  // AndSpecification<Product> green_and_large{green, large};
  // auto green_and_large= ColorSpecification(Color::Green) &&
  // SizeSpecification(Size::Large); auto green_and_large = green && large; auto
  // green_and_large_things = bf.filter(all, green_and_large);
  auto green_and_large_things = bf.filter(all, green && large);

  print_helper(green_things, "green");
  print_helper(large_things, "large");
  print_helper(green_and_large_things, "green_and_large");

  return 0;
}
