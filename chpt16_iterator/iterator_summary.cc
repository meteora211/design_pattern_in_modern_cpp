#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename Container, typename Data>
class Iterator {
public:
  using iter_type = typename vector<Data>::iterator;
  Iterator(Container *container) : container_ptr_(container) {
    iter_ = container_ptr_->container_.begin();
  }
  void first() {
    iter_ = container_ptr_->container_.begin();
  }
  void next() {
    ++iter_;
  }
  bool is_done() {
    return iter_ == container_ptr_->container_.end();
  }
  iter_type current() {
    return iter_;
  }

private:
  Container* container_ptr_;
  iter_type iter_;
};

template<typename T>
class Container {
friend class Iterator<Container, T>;
public:
  void add(T a) {
    container_.push_back(a);
  }
  shared_ptr<Iterator<Container, T>> create_iterator() {
    return make_shared<Iterator<Container, T>>(this);
  }
private:
  vector<T> container_;
};

int main() {
  Container<int> c;
  for (int i = 0; i < 10; ++i) {
    c.add(i);
  }
  auto iter = c.create_iterator();
  for (iter->first(); !iter->is_done(); iter->next()) {
    cout << *(iter->current()) << endl;
  }
}

