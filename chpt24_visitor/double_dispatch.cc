#include <iostream>
#include <string>

using namespace std;

class Visitor;

class Shape {
public:
  virtual void draw() {
    cout << "draw Shape" << endl;
  }
  virtual void accept(Visitor& v);
};

class Rectangle : public Shape {
public:
  void draw() override {
    cout << "draw rectangle" << endl;
  }
  void accept(Visitor& v) override;
};

class Circle : public Shape {
public:
  void draw() override {
    cout << "draw Circle" << endl;
  }
  void accept(Visitor& v) override;
};

class Visitor {
public:
  void visit(Shape& shape) {
    cout << "visit shape" << endl;
    shape.draw();
  }
  void visit(Rectangle& shape) {
    cout << "visit rectangle" << endl;
    shape.draw();
  }
  void visit(Circle& shape) {
    cout << "visit circle" << endl;
    shape.draw();
  }
};

void Shape::accept(Visitor& v) {
  v.visit(*this);
}

void Rectangle::accept(Visitor& v) {
  v.visit(*this);
}

void Circle::accept(Visitor& v) {
  v.visit(*this);
}

class Exportor { // Single Dispatch
public:
  void export_shape(Shape* s) {
    cout << "export shape" << endl;
    s->draw();
  }
  void export_shape(Rectangle* s) {
    cout << "export rectangle" << endl;
    s->draw();
  }
  void export_shape(Circle* s) {
    cout << "export circle" << endl;
    s->draw();
  }
};


int main() {
  cout << "single dispatch can not bind to right export interface." << endl;
  Shape* shape = new Rectangle();
  Exportor().export_shape(shape);

  cout << "\n";

  cout << "double dispatch(visitor) works as expected." << endl;
  Visitor v;
  shape->accept(v);
}
