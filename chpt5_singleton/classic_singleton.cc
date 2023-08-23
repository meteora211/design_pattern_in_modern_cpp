#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

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

class PerthreadSingleton {
public:
  static PerthreadSingleton& get() {
    static thread_local PerthreadSingleton singleton;
    return singleton;
  }
  void print_address() {
    std::cout << "address: " <<  this << std::endl;
  }
  void print_thread_id() {
    std::cout << "thread_id: " << std::this_thread::get_id() << std::endl;
  }
  PerthreadSingleton(const PerthreadSingleton&) = delete;
  PerthreadSingleton(PerthreadSingleton&&) = delete;
  PerthreadSingleton& operator=(const PerthreadSingleton&) = delete;
  PerthreadSingleton& operator=(PerthreadSingleton&&) = delete;
private:
  PerthreadSingleton()=default;

};

int main() {
  auto& singleton = ClassicSingleton::get();
  singleton.print_address();
  auto& singleton_again = ClassicSingleton::get();
  singleton_again.print_address();

  vector<jthread> threads;
  
  mutex mtx;
  auto func = [&mtx](){
    lock_guard lock(mtx);
    auto& singleton = PerthreadSingleton::get();
    singleton.print_address();
    singleton.print_thread_id();
  };
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(func);
  }
}
