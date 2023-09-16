#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum class OutputFormat { markdown, html };

struct ListStrategy {
  virtual void start(ostringstream &oss) = 0;
  virtual void end(ostringstream &oss) = 0;
  virtual void add_list(ostringstream &oss, const string &item) = 0;
};

struct MarkdownStrategy : ListStrategy {
  void start(ostringstream &oss) override { }
  void end(ostringstream &oss) override { }
  void add_list(ostringstream &oss, const string &item) override {
    oss << " * " << item << endl;;
  }
};

struct HTMLStrategy : ListStrategy {
  void start(ostringstream &oss) override {
    oss << "<ul>\n";
  }
  void end(ostringstream &oss) override {
    oss << "<ul>\n";
  }
  void add_list(ostringstream &oss, const string &item) override {
    oss << "  <li>" << item << "<li>\n";
  }
};

struct TextProcessorBase {
  virtual ~TextProcessorBase() {}
  virtual void append_list(const vector<string>& items) = 0;
  string str() {
    return oss.str();
  }
  void clear() {
    oss.str("");
    oss.clear();
  }
  ostringstream oss;
};

struct DynamicTextProcessor : TextProcessorBase {
  explicit DynamicTextProcessor(OutputFormat format=OutputFormat::markdown) {
    set_strategy(format);
  }
  void append_list(const vector<string>& items) override {
    list_strategy->start(oss);
    for (auto item : items) {
      list_strategy->add_list(oss, item);

    }
    list_strategy->end(oss);
  }

  void set_strategy(OutputFormat format) {
    switch (format) {
      case OutputFormat::markdown:
      list_strategy = make_unique<MarkdownStrategy>();
      break;
      case OutputFormat::html:
      list_strategy = make_unique<HTMLStrategy>();
      break;
    }
  }

private:
  unique_ptr<ListStrategy> list_strategy;
};

template<typename Strategy>
struct StaticTextProcessor : TextProcessorBase {
  StaticTextProcessor() : list_strategy{make_unique<Strategy>()} {}
  void append_list(const vector<string>& items) override {
    list_strategy->start(oss);
    for (auto item : items) {
      list_strategy->add_list(oss, item);

    }
    list_strategy->end(oss);
  }


private:
  unique_ptr<Strategy> list_strategy;
};

int main() {
  DynamicTextProcessor tp;
  tp.append_list({"a", "b", "c"});
  cout << tp.str() << endl;
  tp.set_strategy(OutputFormat::html);
  tp.clear();
  tp.append_list({"a", "b", "c"});
  cout << tp.str() << endl;

  StaticTextProcessor<HTMLStrategy> htmlp;
  htmlp.append_list({"a", "b", "c"});
  cout << htmlp.str() << endl;
  StaticTextProcessor<MarkdownStrategy> mkp;
  mkp.append_list({"a", "b", "c"});
  cout << mkp.str() << endl;
}
