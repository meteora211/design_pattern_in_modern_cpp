#include "html_element.h"
using namespace std;

struct HtmlBuilder {
  HtmlElement root;
  HtmlBuilder(std::string root_name) { root.name = root_name; }
  void add_child(std::string child_name, std::string child_text) {
    root.elements.emplace_back(child_name, child_text);
  }
  HtmlBuilder& add_child_fluent(std::string child_name, std::string child_text) {
    root.elements.emplace_back(child_name, child_text);
    return *this;
  }
  std::string str() {
    return root.str();
  }
};

int main() {
  // using HtmlElement directly
  std::string words[] = {"hello", "world"};
  HtmlElement list{"ul", ""};
  for (const auto& w : words) {
    list.elements.emplace_back("li", w);
  }
  std::cout << list.str() << std::endl;

  // using HtmlBuilder
  HtmlBuilder builder{"ul"};
  builder.add_child("li", "hello");
  builder.add_child("li", "world");
  std::cout << builder.str() << std::endl;

  // using fluent HtmlBuilder
  HtmlBuilder fluent_builder{"ul"};
  fluent_builder.add_child_fluent("li", "hello")
                .add_child_fluent("li", "world");
  std::cout << fluent_builder.str() << std::endl;
}
