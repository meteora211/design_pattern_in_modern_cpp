#include <iostream>
#include <string>
#include <memory>
#include <concepts>

using namespace std;

class Car {
public:
  std::string engine;
  int seats;
};
class Manual {
public:
  std::string engine;
  int seats;
};

// XXX: Builder is an interface, use concept to simplify it
class Builder {
public:
  virtual void set_seats(int number) {
    std::cout << "seats: " << number << std::endl;
  }
  virtual void set_engine(std::string engine) {
    std::cout << "engine: " << engine << std::endl;
  }
  virtual ~Builder () {}
};

class CarBuilder : public Builder {
public:
  CarBuilder() : car(std::make_unique<Car>()) {}
  void set_seats(int number) override {
    std::cout << "Car seats: " << number << std::endl;
    car->seats = number;
  }
  void set_engine(std::string engine) override {
    std::cout << "Car engine: " << engine << std::endl;
    car->engine = engine;
  }
  std::unique_ptr<Car> get_result() {
    return std::move(car);
  }
private:
  std::unique_ptr<Car> car;
};

class ManualBuilder : public Builder {
public:
  ManualBuilder() : manual(std::make_unique<Manual>())  {}
  void set_seats(int number) override {
    std::cout << "Manual seats: " << number << std::endl;
    manual->seats = number;
  }
  void set_engine(std::string engine) override {
    std::cout << "Manual engine: " << engine << std::endl;
    manual->engine = engine; }
  std::unique_ptr<Manual> get_result() {
    return std::move(manual);
  }
private:
  std::unique_ptr<Manual> manual;
};

class Director {
public:
  void set_builder(std::shared_ptr<Builder> b) {
    builder = b;
  }
  void build() {
    builder->set_seats(4);
    builder->set_engine("motor");
  }
private:
  std::shared_ptr<Builder> builder;
};

// TODO: 👿 not sure how to implement it with concept
// template<typename T, typename Product>
// template<typename T>
// concept BuilderInterface = requires(T t) {
//   t.set_seats(int{});
//   t.set_engine(std::string{});
//   // t.get_result();
// };

// template<typename Product>
// class BuilderImpl {
// public:
//   BuilderImpl() : product(std::make_unique<Product>()) {}
//   void set_seats(int number) {
//     std::cout << "BuilderImpl set seats: " << number << std::endl;
//     product->seats = number;
//   }
//   void set_engine(std::string engine) {
//     std::cout << "BuilderImpl set engine: " << engine << std::endl;
//     product->engine = engine;
//   }
//   std::unique_ptr<Product> get_result() {
//     return std::move(product);
//   }
// private:
//   std::unique_ptr<Product> product;
// };

// template<typename Product>
// void build_interface(BuilderImpl<Product> builder) {
//   builder.set_seats(4);
//   builder.set_engine("motor");
// }

int main() {
  auto builder = std::make_shared<CarBuilder>();
  auto director = Director();
  director.set_builder(builder);
  director.build();
  auto car = builder->get_result();

  // auto car_builder = BuilderImpl<Manual>();
  // build_interface(car_builder)
}
