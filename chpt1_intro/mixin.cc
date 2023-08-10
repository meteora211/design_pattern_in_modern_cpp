#include <iostream>
#include <string>

using namespace std;

template <typename Printable> struct RepeatPrintable : Printable {
  explicit RepeatPrintable(const Printable &printable) : Printable(printable) {}

  void repeat(int n) {
    for (auto i = 0; i < n; ++i) {
      this->print();
    }
  }
};

class Name {
public:
  Name(std::string firstName, std::string lastName)
      : firstName_(std::move(firstName)), lastName_(std::move(lastName)) {}

  void print() const {
    std::cout << firstName_ << ", " << lastName_ << std::endl;
  }

private:
  std::string firstName_;
  std::string lastName_;
};

template <typename Printable>
RepeatPrintable<Printable> repeatPrintable(const Printable &p) {
  return RepeatPrintable<Printable>(p);
}

int main() {
  Name czr("Zhaorui", "Chen");
  repeatPrintable(czr).repeat(5);
}
