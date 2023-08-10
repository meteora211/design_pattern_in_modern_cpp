#include <concepts>
#include <iostream>
#include <string_view>

using namespace std;

template <typename TImpl>
concept IsNotifier = requires(TImpl t) {
  t.alertSMS(std::string_view{});
  t.alertEmail(std::string_view{});
};

class TestNotifier {
public:
  void alertSMS(std::string_view msg) {
    std::cout << "Test AlertSMS: " << msg << std::endl;
  }
  void alertEmail(std::string_view msg) {
    std::cout << "Test AlertEmail: " << msg << std::endl;
  }
};

// XXX: alertAll interface provide an abstract interface by concept IsNotifier
template <IsNotifier TImpl>
void alertAll(TImpl &notifier, std::string_view msg) {
  notifier.alertSMS(msg);
  notifier.alertEmail(msg);
}

int main() {
  TestNotifier tn;
  alertAll(tn, "alert msg");
}
