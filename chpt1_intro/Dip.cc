// Dependency Inversion Principle
// - High-level modules should not depend on low-level modules. Both should
// depend on abstractions.
// - Abstractions should not depend on details. Details should depend on
// abstractions.

// ref:
// https://boost-ext.github.io/di/index.html
#include <boost/di.hpp>
#include <iostream>
#include <memory>
#include <string>
namespace di = boost::di;

using namespace std;
using std::string;

struct ILogger {
  ILogger() = default;
  virtual ~ILogger() {}
  virtual void log(const string &s) const = 0;
};

struct ConsoleLogger : ILogger {
  ConsoleLogger() {}
  void log(const string &s) const override {
    std::cout << "Console Log: " << s << std::endl;
  }
};

class Reporting {
  const ILogger &logger;

public:
  Reporting(const ILogger &logger) : logger{logger} {}
  void prepare_report() { logger.log("Preparing the report"); }
};

struct Engine {
  float volume = 5;
  int horse_power = 400;
  friend ostream &operator<<(ostream &os, const Engine &obj) {
    return os << "volume: " << obj.volume
              << " horse_power: " << obj.horse_power;
  }
};

struct Car {
  std::unique_ptr<Engine> engine;
  std::shared_ptr<ILogger> logger;
  Car(std::unique_ptr<Engine> engine, const std::shared_ptr<ILogger> &logger)
      : engine{std::move(engine)}, logger{logger} {
    logger->log("making a car");
  }
  friend ostream &operator<<(ostream &os, const Car &obj) {
    return os << "car with engine: " << *obj.engine;
  }
};

int main() {
  auto injector = di::make_injector(di::bind<ILogger>().to<ConsoleLogger>());
  auto car = injector.create<std::shared_ptr<Car>>();
  return 0;
}
