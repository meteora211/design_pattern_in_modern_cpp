#include <iostream>
#include <memory>

using namespace std;

class Device {
public:
  Device() = default;
  virtual ~Device() = default;
  bool isEnable() {
    return enable_;
  }
  virtual void enable() {
    cout << "enable device" << endl;
    enable_ = true;
  }
  virtual void disable() {
    cout << "disable device" << endl;
    enable_ = false;
  }
protected:
  bool enable_;
};

class Remote {
public:
  Remote() : device_(make_unique<Device>()) {}
  Remote(unique_ptr<Device> device) : device_(std::move(device)) {}
  void togglePower() {
    if (device_->isEnable()) {
      device_->disable();
    } else {
      device_->enable();
    }
  }
private:
  unique_ptr<Device> device_;
};

class Radio : public Device {
  void enable() override {
    cout << "enable Radio" << endl;
    enable_ = true;
  }
  void disable() override {
    cout << "disable Radio" << endl;
    enable_ = false;
  }
};

class TV : public Device {
  void enable() override {
    cout << "enable TV" << endl;
    enable_ = true;
  }
  void disable() override {
    cout << "disable TV" << endl;
    enable_ = false;
  }
};

int main () {
  auto tv_remote = Remote(make_unique<TV>());
  tv_remote.togglePower();
  tv_remote.togglePower();
  auto rd_remote = Remote(make_unique<Radio>());
  rd_remote.togglePower();
  rd_remote.togglePower();
}
