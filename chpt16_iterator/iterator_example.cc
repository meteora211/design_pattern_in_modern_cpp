#include <iostream>
#include <memory>
#include <string>

using namespace ::std;

template <typename T> class BinaryTree;

template <typename T> class Node {
public:
  Node(const T &value) : value{value} {}
  Node(const T &value, Node<T> *left, Node<T> *right)
      : value{value}, left{left}, right{right} {
    this->left->tree = this->right->tree = tree;
    this->left->parent = this->right->parent = this;
  }
  T value;
  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;
  BinaryTree<T> *tree;

  void set_tree(BinaryTree<T> *t) {
    tree = t;
    if (left) {
      left->set_tree(t);
    }
    if (right) {
      right->set_tree(t);
    }
  }
};

template <typename T> struct PreOrderIterator {
  PreOrderIterator(T *cur) : cur{cur} {}
  PreOrderIterator<T> &operator++() {
    if (cur->left) {
      cur = cur->left;
    } else if (cur->right) {
      cur = cur->right;
    } else {
      auto parent = cur->parent;
      while (parent && cur == parent->right) {
        cur = parent;
        parent = parent->parent;
      }
      if (parent) {
        cur = parent->right;
      } else {
        cur = nullptr;
      }
    }
    return *this;
  }
  PreOrderIterator<T> operator++(int) {
    auto old = *this;
    ++(*this);
    return old;
  }

  bool operator!=(const PreOrderIterator<T> &other) { return cur != other.cur; }
  T &operator*() { return *cur; }
  T *cur;
};

template <typename T> class BinaryTree {
public:
  using iterator = PreOrderIterator<Node<T>>;
  explicit BinaryTree(Node<T> *root) : root(root) {
    // NOTE: shared_ptr could be tricky in set_tree which requires
    // enable_shared_from_this. But shared_from_this could not be used in ctor.
    root->set_tree(this);
  }
  iterator begin() { return iterator(root); }
  iterator end() { return iterator(nullptr); }
  Node<T> *root;
  ~BinaryTree() {
    for (auto iter = begin(); iter != end();) {
      // NOTE: could not use ++iter here which breaks pointer in loop
      auto old = iter++;
      delete old.cur;
    }
  }
};

int main() {
  BinaryTree<int> tree{
      new Node<int>{1, new Node<int>{2, new Node<int>{4}, new Node<int>{5}},
                    new Node<int>(3, new Node<int>{6}, new Node<int>{7})}};
  for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
    cout << (*iter).value << endl;
  }
}
