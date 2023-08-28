#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

struct SharedState {
  std::string brand_;
  std::string model_;
  std::string color_;

  SharedState(const std::string &brand, const std::string &model,
              const std::string &color)
      : brand_(brand), model_(model), color_(color) {}
  SharedState(const SharedState &s)
      : brand_(s.brand_), model_(s.model_), color_(s.color_) {}

  friend std::ostream &operator<<(std::ostream &os, const SharedState &ss) {
    return os << "[ " << ss.brand_ << " , " << ss.model_ << " , " << ss.color_
              << " ]";
  }
};

struct UniqueState {
  std::string owner_;
  std::string plates_;

  UniqueState(const std::string &owner, const std::string &plates)
      : owner_(owner), plates_(plates) {}

  friend std::ostream &operator<<(std::ostream &os, const UniqueState &us) {
    return os << "[ " << us.owner_ << " , " << us.plates_ << " ]";
  }
};

class FlyWeight {
public:
  FlyWeight() = default;
  FlyWeight(const SharedState &shared_state)
      : shared_state_(make_shared<SharedState>(shared_state)) {}
  FlyWeight(shared_ptr<SharedState> shared_state)
      : shared_state_{shared_state} {}
  FlyWeight(const FlyWeight &other) : shared_state_{other.shared_state_} {}
  void operation(const UniqueState &unique_state) {
    cout << "FlyWeight display shared state: " << *shared_state_
         << " and unique state: " << unique_state << endl;
  }

private:
  shared_ptr<SharedState> shared_state_;
};

class FlyWeightFactory {
public:
  FlyWeightFactory(std::initializer_list<SharedState> states) {
    for (auto state : states) {
      weights_.insert(make_pair(get_key(state), state));
    }
  }
  FlyWeight &get(const SharedState &state) {
    auto key = get_key(state);
    if (weights_.find(key) != weights_.end()) {
      return weights_.at(key);
    } else {
      weights_.insert(make_pair(key, state));
      return weights_.at(key);
    }
  }

private:
  string get_key(const SharedState &state) {
    return state.brand_ + "_" + state.model_ + "_" + state.color_;
  }
  unordered_map<string, FlyWeight> weights_;
};

// XXX: why need flyweight class? instread of using SharedState directly in FlyWeightFactory ?
// class Context {
// public:
//   Context(FlyWeightFactory& factory, const SharedState sstate, UniqueState ustate) :
//   unique_state_{make_unique<UniqueState>(ustate)}
//   {
//     flyweight_ = factory.get(sstate);
//   }
//   void operation() {

//   }
// private:
//   FlyWeight flyweight_;
//   unique_ptr<UniqueState> unique_state_;
// };

int main() {
  FlyWeightFactory factory{{"Chevrolet", "Camaro2018", "pink"},
                           {"Mercedes Benz", "C300", "black"},
                           {"Mercedes Benz", "C500", "red"},
                           {"BMW", "M5", "red"},
                           {"BMW", "X6", "white"}};
  factory.get({"BMW", "X6", "white"}).operation({"John", "CL234IR"});
}
