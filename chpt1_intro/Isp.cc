// Interface Segregation Principle
#include <iostream>

// XXX: IMachine breaks ISP, it forces derived class to implement 3 interfaces.
// struct IMachine {
//   virtual void print() = 0;
//   virtual void fax() = 0;
//   virtual void scan() = 0;
// }

// XXX: IMachine follows ISP
struct IPrinter {
  virtual void print() = 0;
};
struct IScanner {
  virtual void scan() = 0;
};
struct Printer: IPrinter {
  void print() override {
    std::cout << "print" << std::endl;
  }
};
struct Scanner: IScanner {
  void scan() override {
    std::cout << "scan" << std::endl;
  }
};
struct IMachine : IPrinter, IScanner {};
struct Machine : IMachine {
  Machine(IPrinter& printer, IScanner& scanner)
    : printer{printer},
      scanner{scanner} {}
  IPrinter& printer;
  IScanner& scanner;
  void print() override {
    std::cout << "Machine start" << std::endl;
    printer.print();
  }
  void scan() override {
    std::cout << "Machine start" << std::endl;
    scanner.scan();
  }
};

int main() {
  auto p = Printer();
  auto s = Scanner();
  Machine m{p, s};
  m.print();
  m.scan();
}
