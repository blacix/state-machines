#ifndef STATE_MACHINES_TEMPLATE_ID_HPP
#define STATE_MACHINES_TEMPLATE_ID_HPP
#include <iostream>
#include <map>
#include <memory>

namespace template_id {

// Forward declaration
template<typename StateIdType>
class StateMachine;

// Base State class
template<typename StateIdType>
class State {
public:
  State(const State&) = delete;
  State(State&&) = delete;
  State& operator=(const State&) = delete;
  State& operator=(State&&) = delete;
  virtual ~State() = default;
  virtual void enter() = 0;
  virtual void exit() = 0;
  virtual void update(StateMachine<StateIdType>& stateMachine) = 0;

  StateIdType getStateId() const { return mStateId; }

protected:
  explicit State(StateIdType id)
      : mStateId(id) {}

  StateIdType mStateId;
};

// State Machine class
template<typename StateIdType>
class StateMachine {
public:
  void addState(std::unique_ptr<State<StateIdType>> state) {
    states[state->getStateId()] = std::move(state);
  }

  void setInitialState(StateIdType stateId) {
    currentState = states[stateId].get();
    if (currentState) {
      currentState->enter();
    }
  }

  void changeState(StateIdType newStateId) {
    if (currentState) {
      currentState->exit();
    }
    currentState = states[newStateId].get();
    if (currentState) {
      currentState->enter();
    }
  }

  void update() {
    if (currentState) {
      currentState->update(*this);
    }
  }

private:
  std::map<StateIdType, std::unique_ptr<State<StateIdType>>> states;
  State<StateIdType> *currentState = nullptr;
};

// Example usage
enum class GameState {
  MENU,
  PLAYING,
};

class MenuState : public State<GameState> {
public:
  MenuState()
      : State(GameState::MENU) {}
  void enter() override { std::cout << "Entering Menu State\n"; }
  void exit() override { std::cout << "Exiting Menu State\n"; }
  void update(StateMachine<GameState>& stateMachine) override {
    std::cout << "Updating Menu State\n";
    stateMachine.changeState(GameState::PLAYING);
  }
};

class PlayingState : public State<GameState> {
public:
  PlayingState()
      : State(GameState::PLAYING) {}
  void enter() override { std::cout << "Entering Playing State\n"; }
  void exit() override { std::cout << "Exiting Playing State\n"; }
  void update(StateMachine<GameState>& stateMachine) override {
    std::cout << "Updating Playing State\n";
    stateMachine.changeState(GameState::MENU);
  }
};

void test() {
  StateMachine<GameState> gameSM;

  gameSM.addState(std::make_unique<MenuState>());
  gameSM.addState(std::make_unique<PlayingState>());
  gameSM.setInitialState(GameState::MENU);
  gameSM.update();
  gameSM.update();
}

}// namespace template_id

#endif//STATE_MACHINES_TEMPLATE_ID_HPP
