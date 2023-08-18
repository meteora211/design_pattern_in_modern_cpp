#include <iostream>
#include <string>
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

class MacButton : public Button {
public:
  void on_click() override {
    std::cout << "click mac button" << std::endl;
  }
  void render() override {
    std::cout << "render mac button" << std::endl;
  }
};

class Checkbox {
public:
  virtual void on_check() = 0;
  virtual void render() = 0;
};

class WindowsCheckbox : public Checkbox {
public:
  void on_check() override {
    std::cout << "click windows checkbox" << std::endl;
  }
  void render() override {
    std::cout << "render windows checkbox" << std::endl;
  }
};

class MacCheckbox : public Checkbox {
public:
  void on_check() override {
    std::cout << "click mac checkbox" << std::endl;
  }
  void render() override {
    std::cout << "render mac checkbox" << std::endl;
  }
};


class GUIFactory {
public:
  virtual unique_ptr<Button> create_button() = 0;
  virtual unique_ptr<Checkbox> create_checkbox() = 0;
};

class WindowsFactory : public GUIFactory {
  unique_ptr<Button> create_button() override {
    return make_unique<WindowsButton>();
  }
  unique_ptr<Checkbox> create_checkbox() override {
    return make_unique<WindowsCheckbox>();
  }
};

class MacFactory : public GUIFactory {
  unique_ptr<Button> create_button() override {
    return make_unique<MacButton>();
  }
  unique_ptr<Checkbox> create_checkbox() override {
    return make_unique<MacCheckbox>();
  }
};

class Application {
public:
  Application(const std::string& kind) {
    if (kind == "windows") {
      factory = make_unique<WindowsFactory>();
    } else if (kind == "html") {
      factory = make_unique<MacFactory>();
    }
  }
  void render_button() {
    button = factory->create_button();
    button->render();
  }
  void render_checkbox() {
    checkbox = factory->create_checkbox();
    checkbox->render();
  }
private:
  unique_ptr<GUIFactory> factory;
  unique_ptr<Button> button;
  unique_ptr<Checkbox> checkbox;

};

int main() {
  Application("windows").render_button();
}
