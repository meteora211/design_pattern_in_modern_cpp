#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ChatRoom;

struct Person {
  Person(const string& name) : name{name} {}
  string name;
  ChatRoom* room;
  vector<string> chat_log;
  void recieve(const string& origin, const string& message) {
    string s{origin + ": \"" + message + "\""};
    cout << "[" << name << "'s chat session] " << s << endl;
    chat_log.emplace_back(s);
  }
  void say(const string& message) const;
  void pm(const string& who, const string& message) const;
};

struct ChatRoom {
  vector<Person*> people;
  void join(Person* p) {
    string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);
    p->room = this;
    people.push_back(p);
  }
  void broadcast(const string& origin, const string& message) {
    for (auto* p : people) {
      if (p->name != origin) {
        p->recieve(origin, message);
      }
    }
  }
  void message(const string& from, const string& to, const string& message) {
    auto target = find_if(begin(people), end(people), [&](const Person* p){
      return p->name == to;
    });
    if (target != end(people)) {
      (*target)->recieve(from, message);
    }
  }
};

void Person::say(const string& message) const {
  room->broadcast(name, message);
}

void Person::pm(const string& origin, const string& message) const {
  room->message(name, origin, message);
}

int main() {
  ChatRoom cm;
  Person john{"john"};
  Person jane{"jane"};
  cm.join(&john);
  cm.join(&jane);

  john.say("hello jane");
  jane.say("hello john");

  Person simon{"simon"};
  cm.join(&simon);
  simon.say("hello everyone");
  jane.pm("simon", "hi");
}
