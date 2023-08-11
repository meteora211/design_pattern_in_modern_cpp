// Single Responsibility Principle (SRP)
#include <string>
#include <vector>
#include <iostream>
// #include <format>

using namespace std;

struct Journal {
  std::string title;
  std::vector<std::string> entries;

  explicit Journal(const std::string& title) : title{title} {}

  void add(const std::string& entry) {
    static int count = 1;
    // entries.push_back(std::format("{}: {}", count++, entry));
    entries.push_back(std::to_string(count) + ": " + entry);
  }

  // XXX: this break the SRP.
  // void save(const string& filename) {
  //   // Use print instead of actual save
  //   std::cout << "saving to: " << filename << std::endl;
  //   for (auto& s : entries) {
  //     std::cout << s << std::endl;
  //   }
  // }
};

struct PersistenceManager {
  static void save(const Journal& j, const string& filename) {
    // Use print instead of actual save
    std::cout << "saving to: " << filename << std::endl;
    for (auto& s : j.entries) {
      std::cout << s << std::endl;
    }
  }
};

int main() {
  Journal j{"Dear Diary"};
  j.add("I cried today");
  j.add("I write a bug");
  // XXX: this break the SRP.
  // j.save("temp_file");
  PersistenceManager::save(j, "temp_file");
}
