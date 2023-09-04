#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct Token {
  enum Type { interger, plus, minus, lparen, rparen } type;
  string text;
  explicit Token(Type type, const string &text) : type{type}, text{text} {}
  friend ostream &operator<<(ostream &os, const Token &obj) {
    return os << "`" << obj.text << "`";
  }
};

vector<Token> lex(const string &input) {
  vector<Token> result;
  for (size_t i = 0; i < input.size(); ++i) {
    switch (input[i]) {
    case '+':
      result.emplace_back(Token::plus, "+");
      break;
    case '-':
      result.emplace_back(Token::minus, "-");
      break;
    case '(':
      result.emplace_back(Token::lparen, "(");
      break;
    case ')':
      result.emplace_back(Token::rparen, ")");
      break;
    default:
      // number ???
      break;
    }
  }
  return result;
}

int main() {
  // chapter skiped.
  cout << "Not impl" << endl;
}
