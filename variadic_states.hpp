#ifndef STATE_MACHINES_VARIADIC_STATES_HPP
#define STATE_MACHINES_VARIADIC_STATES_HPP
#include <iostream>
#include <type_traits>
#include <variant>

namespace variadic_states {
// Forward declaration of the StateMachine class
template<typename... States>
class StateMachine;

// Base State class
class State {
public:
  virtual ~State() = default;
  virtual void entry() {}
  virtual void exit() {}
  virtual void update() {}
};

// StateMachine class
template<typename... States>
class StateMachine {
private:
  std::variant<States...> mCurrentState;
  std::tuple<States...> mStates;

  template<typename T>
  static constexpr bool is_valid_state = (std::is_base_of_v<State, T>);

public:
  StateMachine()
      : mCurrentState(std::get<0>(mStates)) {
    static_assert((is_valid_state<States> && ...), "All states must inherit from the State class");
  }

  template<typename T>
  void transition() {
    static_assert(is_valid_state<T>, "Invalid state type");

    std::visit([](auto& state) { state.exit(); }, mCurrentState);
    mCurrentState = std::get<T>(mStates);
    std::visit([](auto& state) { state.entry(); }, mCurrentState);
  }

  template<typename T>
  bool is_in_state() const {
    return std::holds_alternative<T>(mCurrentState);
  }

  void update() {
    std::visit([](auto& state) { state.update(); }, mCurrentState);
  }
};

// Example usage
class StateA : public State {
public:
  void entry() override { std::cout << "Entering State A" << std::endl; }
  void exit() override { std::cout << "Exiting State A" << std::endl; }
  void update() override { std::cout << "Updating State A" << std::endl; }
};

class StateB : public State {
public:
  void entry() override { std::cout << "Entering State B" << std::endl; }
  void exit() override { std::cout << "Exiting State B" << std::endl; }
  void update() override { std::cout << "Updating State B" << std::endl; }
};

void test() {
  StateMachine<StateA, StateB> sm;

  sm.update();
  sm.transition<StateB>();
  sm.update();
  sm.transition<StateA>();
}

}// namespace variadic_states
#endif//STATE_MACHINES_VARIADIC_STATES_HPP
