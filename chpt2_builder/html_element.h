#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct HtmlBuilder;
struct HtmlElement {
  std::string name, text;
  std::vector<HtmlElement> elements;

  HtmlElement() = default;
  HtmlElement(const std::string &name, const std::string &text)
      : name(name), text(text) {}

  std::string str(int indent = 0) const {
    // ugly implement just for example 
    std::string result;
    std::string indent_str(indent, ' ');
    std::string begin = indent_str + "<" + name + ">\n";
    std::string end = indent_str + "</" + name + ">\n";
    std::string body = indent_str + "  " + text + "\n";
    for (auto elem : elements) {
      body += elem.str(indent+2);
    }
    return begin + body + end;
  }
};


