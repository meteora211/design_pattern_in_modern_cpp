#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct Tag {
  std::string name;
  std::string text;
  std::vector<Tag> children;
  std::vector<std::pair<std::string, std::string>> attributes;

  friend ostream& operator<<(ostream& os, const Tag& tag) {
    std::cout << " just a demo " << std::endl;
    return os;
  }
protected:
  Tag(const std::string& name, const std::string& text): name(name), text(text) {}
  Tag(const std::string& name, const std::vector<Tag>& children): name(name), children(children) {}
};

struct P : public Tag {
  explicit P(const std::string& text) : Tag{"p", text} {}
  explicit P(const std::initializer_list<Tag>& children) : Tag{"p", children} {}
};

struct IMG : public Tag {
  explicit IMG(const std::string& url) : Tag{"img", ""} {
    attributes.emplace_back("src", url);
  }
};

int main() {
  std::cout << P { IMG { "img"} } << std::endl;
}
