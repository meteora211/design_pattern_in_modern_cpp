// Open-Closed Principle
#include <string>
#include <vector>

using namespace std;

enum class Color { Red, Green, Blue};
enum class Size { Small, Medium, Large};

struct Product {
  string name;
  Color color;
  Size size;
};

struct ProductFilter {
  typedef std::vector<Product*> Items;

  Items by_color(Items items, Color color) {
    Items result;
    for (auto* item : items) {
      if (item->color == color) {
        result.push_back(item);
      }
    }
    return result;
  }

  Items by_size(Items items, Size size) {
    Items result;
    for (auto* item : items) {
      if (item->size == size) {
        result.push_back(item);
      }
    }
    return result;
  }

  Items by_color_and_size(Items items, Color color, Size size) {
    Items result;
    for (auto* item : items) {
      if (item->color == color && item->size == size) {
        result.push_back(item);
      }
    }
    return result;
  }

};

int main() {
  return 0;
}
