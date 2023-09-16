#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Game {
public:
  explicit Game(int player_num) : player_num{player_num} {}
  // template method
  void run() {
    start();
    while (!have_winner()) {
      take_turn();
    }
    cout << "Player " << get_winner() << " wins.\n";
  }

protected:
  virtual void start() = 0;
  virtual bool have_winner() = 0;
  virtual void take_turn() = 0;
  virtual int get_winner() = 0;
  int player_num;
  int cur_player{0};
};

class Chess : public Game {
public:
  explicit Chess() : Game{2} {}

protected:
  void start() override {}
  bool have_winner() override { return turns == max_turns; }
  void take_turn() override {
    cout << "Turn " << turns << " taken by player: " << cur_player << endl;
    turns++;
    cur_player = (cur_player + 1) % player_num;
  }
  int get_winner() override { return cur_player; }

private:
  int turns{0}, max_turns{10};
};

struct GameState {
  int cur_player, win_player, player_num;
};

template <typename FnStartAction, typename FnTakeTurnAction,
          typename FnHaveWinnerAction>
void run_game(GameState init_state, FnStartAction start_action,
              FnTakeTurnAction turn_action, FnHaveWinnerAction winner_action) {
  GameState state = init_state;
  start_action(state);
  while (!winner_action(state)) {
    turn_action(state);
  }
  cout << "Player " << state.win_player << " wins.\n";
}

int main() {
  Chess().run();

  int turn{0}, max_turns{10};
  GameState state{.cur_player = 0, .win_player = -1, .player_num = 2};
  auto start = [](GameState& state){
    cout << "Chess start" << endl;
  };
  auto take_turn = [&](GameState& state) {
    cout << "Turn " << turn << " taken by player: " << state.cur_player << endl;
    turn++;
    state.cur_player = (state.cur_player + 1) % state.player_num;
    state.win_player = state.cur_player;
  };
  auto have_winner = [&](GameState& state) {
    return turn == max_turns;
  };
  run_game(state, start, take_turn, have_winner);
}
