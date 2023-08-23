#include <iostream>

using namespace std;
class RoundPeg {
public:
  RoundPeg() = default;
  RoundPeg(float radius): radius{radius} {}
  virtual float get_radius() const {
    return radius;
  }
private:
  float radius;
};

class SquarePeg {
public:
  SquarePeg() = default;
  SquarePeg(float width): width{width} {}
  float get_width() const {
    return width;
  }
private:
  float width;
};

class RoundHole {
public:
  RoundHole(float radius): radius{radius} {}
  float get_radius() const {
    return radius;
  }
  bool fit(const RoundPeg& peg) const {
    return radius == peg.get_radius();
  }
private:
  float radius;
};


class SquarePegAdapter : public RoundPeg {
public:
  SquarePegAdapter(SquarePeg peg) : peg{peg} {}
  float get_radius() const override {
    cout << "ADPTER" << endl;
    // may need some tranform...
    return peg.get_width();
  }
private:
  SquarePeg peg;
};

int main() {
  RoundHole rh{3};
  RoundPeg rp{3};
  cout << rh.fit(rp) << endl;
  SquarePeg sp{3};
  SquarePegAdapter adapter{sp};
  cout << rh.fit(adapter) << endl;
}
