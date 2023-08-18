#include <iostream>
#include <memory>

using namespace std;

class Button {
public:
  virtual void on_click() = 0;
  virtual void render() = 0;
};

class WindowsButton : public Button {
public:
  void on_click() override {
    std::cout << "click windows button" << std::endl;
  }
  void render() override {
    std::cout << "render windows button" << std::endl;
  }
};

class HTMLButton : public Button {
public:
  void on_click() override {
    std::cout << "click html button" << std::endl;
  }
  void render() override {
    std::cout << "render html button" << std::endl;
  }
};

class ButtonCreator {
public:
  void render() {
    auto button = create_button();
    button->on_click();
    button->render();
  }
  virtual std::unique_ptr<Button> create_button() = 0;
  virtual ~ButtonCreator() {} 
};

class WindowsButtonCreator : public ButtonCreator {
public:
  unique_ptr<Button> create_button() override {
    return make_unique<WindowsButton>();
  }
};

class HTMLButtonCreator : public ButtonCreator {
public:
  std::unique_ptr<Button> create_button() override {
    return make_unique<HTMLButton>();
  }
};

class Application {
public:
  Application(const std::string& kind) {
    if (kind == "windows") {
      creator = make_unique<WindowsButtonCreator>();
    } else if (kind == "html") {
      creator = make_unique<HTMLButtonCreator>();
    }
  }
  void render() {
    creator->render();
  }
private:
  unique_ptr<ButtonCreator> creator;
};

int main() {
  // WindowsButtonCreator().render();
  Application("html").render();
}
