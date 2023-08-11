
class Person {
  int age_;

public:
  int get_age() const { return age_; }
  void set_age(int value) { age_ = value; }
  // non-stardard declaration specifier in MSVC/clang
  // __declspec(property(get=get_age, put=set_age)) int age;
};

int main() {
  Person p;
  // with __declspec enable:
  // p.age = 20;
  p.set_age(20);
}
