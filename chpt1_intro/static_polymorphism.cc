#include <iostream>
#include <string>
#include <string_view>

using namespace std;
// actually a CRTP

template <typename TImpl> class Notifier {
public:
  void alertSMS(std::string_view msg) { impl().sendAlertSMS(msg); }
  void alertEmail(std::string_view msg) { impl().sendAlertEmail(msg); }

private:
  TImpl &impl() { return static_cast<TImpl &>(*this); }
  // friend TImpl;
};

class TestNotifier : public Notifier<TestNotifier> {
public:
  void sendAlertSMS(std::string_view msg) {
    std::cout << "Test AlertSMS: " << msg << std::endl;
  }
  void sendAlertEmail(std::string_view msg) {
    std::cout << "Test AlertEmail: " << msg << std::endl;
  }
};

// XXX: alertAll interface provide an abstract interface.
// `Notifier<TImpl>` uses CRTP to achieve static polymorphism
template <typename TImpl>
void alertAll(Notifier<TImpl> &notifier, std::string_view msg) {
  notifier.alertSMS(msg);
  notifier.alertEmail(msg);
}

int main() {
  TestNotifier tn;
  alertAll(tn, "alert msg");
}
