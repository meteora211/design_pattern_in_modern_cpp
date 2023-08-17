#include <iostream>
#include <memory>
#include <vector>

using Point2D = std::vector<float>;

enum class Material { brick, aerated_concrete, drywall };
enum class WallType { basic, main, partition };

class Wall {
protected:
  Point2D start, end;
  int elevation, height;

public:
  Wall(Point2D start, Point2D end, int elevation, int height)
      : start{start}, end{end}, elevation{elevation}, height{height} {}
  virtual ~Wall() {}
  virtual void print() const {
    std::cout << "start: " << start[0] << " " << start[1] << " end: " << end[0]
              << " " << end[1] << " elevation: " << elevation
              << " height: " << height;
  }
};

class SolidWall : public Wall {
  int width;
  Material material;

public:
  // SolidWall(Point2D start, Point2D end, int elevation, int height, int width,
  // Material material) : Wall(start, end, elevation, height), width{width},
  // material{material} {
  //   if (elevation < 0 && material == Material::aerated_concrete) throw
  //   std::invalid_argument("elevation"); if (width < 120 && material ==
  //   Material::brick) throw std::invalid_argument("width");
  // }
  // XXX: the code in book uses PROTECTED ctor which is wrong. It is not
  // possible to use make_unique of a protected ctor. SEE:
  // https://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const/8147213#8147213
  void print() const override {
    std::cout << "start: " << start[0] << " " << start[1] << " end: " << end[0]
              << " " << end[1] << " elevation: " << elevation
              << " height: " << height << " width: " << width
              << " material: " << int(material);
  }
  SolidWall(Point2D start, Point2D end, int elevation, int height, int width,
            Material material)
      : Wall(start, end, elevation, height), width{width}, material{material} {}
  friend class WallFactory;
};

std::ostream &operator<<(std::ostream &os, const Wall &obj) {
  obj.print();
  return os;
}

class WallFactory {
public:
  static std::unique_ptr<Wall> create_main(Point2D start, Point2D end,
                                           int elevation, int height) {
    return std::make_unique<SolidWall>(start, end, elevation, height, 375,
                                       Material::aerated_concrete);
  }
  static std::unique_ptr<Wall> create_partition(Point2D start, Point2D end,
                                                int elevation, int height) {
    return std::make_unique<SolidWall>(start, end, elevation, height, 120,
                                       Material::brick);
  }
  static std::unique_ptr<Wall> create_wall(Point2D start, Point2D end,
                                           int elevation, int height) {
    return std::make_unique<Wall>(start, end, elevation, height);
  }
  static std::unique_ptr<Wall> create_wall(WallType type, Point2D start,
                                           Point2D end, int elevation,
                                           int height) {
    switch (type) {
      using enum WallType;
    case basic:
      return create_main(start, end, elevation, height);
    case main:
      return create_main(start, end, elevation, height);
    case partition:
      return create_partition(start, end, elevation, height);
    }
  }
};

int main() {
  const auto main_wall =
      WallFactory::create_main({0, 0}, {0, 3000}, 2700, 3000);
  std::cout << *main_wall << std::endl;
}
