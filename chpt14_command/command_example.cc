#include <iostream>
#include <memory>
#include <string>

using namespace std;

class BankAccount { // Reciver
public:
  int balance = 0;
  int overdraft_limit = -500;
  void deposite(int amount) {
    balance += amount;
    cout << "deposite " << amount << " balance is: " << balance << endl;
  }
  void withdraw(int amount) {
    if (balance - amount > overdraft_limit) {
      balance -= amount;
      cout << "withdraw " << amount << " balance is: " << balance << endl;
    }
  }
};

class Command { // Command
public:
  virtual ~Command() = default;
  virtual void call() const = 0;
};

struct BankAccountCommand : public Command { // ConcreteCommand
private:
  shared_ptr<BankAccount> account;
public:
  enum Action {
    deposite,
    withdraw,
  } action;
  BankAccountCommand(shared_ptr<BankAccount> account, Action action, int amount) : account{account}, action(action), amount(amount) {}

  void call() const override {
    switch(action) {
      case deposite:
        account->deposite(amount);
        break;
      case withdraw:
        account->withdraw(amount);
        break;
    }
  }
private:
  int amount;
};

int main() {
  // Invoker, which is client code.
  auto account = make_shared<BankAccount>();
  auto cmd = make_shared<BankAccountCommand>(account, BankAccountCommand::deposite, 100);
  cmd->call();
}
