#include <iostream>

class ClassicSingleton {
public:
  static ClassicSingleton& get() {
    static ClassicSingleton singleton;
    return singleton;
  }
  void print_address() {
    std::cout << this << std::endl;
  }
  ClassicSingleton(const ClassicSingleton&) = delete;
  ClassicSingleton(ClassicSingleton&&) = delete;
  ClassicSingleton& operator=(const ClassicSingleton&) = delete;
  ClassicSingleton& operator=(ClassicSingleton&&) = delete;
private:
  ClassicSingleton()=default;
};

int main() {
  auto& singleton = ClassicSingleton::get();
  singleton.print_address();
  auto& singleton_again = ClassicSingleton::get();
  singleton_again.print_address();
}
