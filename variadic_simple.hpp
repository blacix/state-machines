#ifndef STATE_MACHINES_VARIADIC_SIMPLE_HPP
#define STATE_MACHINES_VARIADIC_SIMPLE_HPP
#include <iostream>
#include <type_traits>
#include <variant>

namespace variadic_simple {

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

  template<typename EventType>
  void handle(EventType event) {
    std::visit([event](auto& state) { state.handle(event); }, mCurrentState);
  }
};


struct TestEvent1 {};
struct TestEvent2 {};

// Example usage
class StateA : public State {
public:
  void entry() override { std::cout << "Entering State A" << std::endl; }
  void exit() override { std::cout << "Exiting State A" << std::endl; }
  void update() override { std::cout << "Updating State A" << std::endl; }
  template<typename EventType>
  void handle(EventType event) {
    std::cout << "Unhandled event in State A" << std::endl;
  }
};

template<>
void StateA::handle<class TestEvent1>(TestEvent1 event) {
  std::cout << "TestEvent1 in State A" << std::endl;
}

class StateB : public State {
public:
  void entry() override { std::cout << "Entering State B" << std::endl; }
  void exit() override { std::cout << "Exiting State B" << std::endl; }
  void update() override { std::cout << "Updating State B" << std::endl; }
  template<typename EventType>
  void handle(EventType event) {
    std::cout << "Unhandled event in State B" << std::endl;
  }
};

template<>
void StateB::handle<class TestEvent2>(TestEvent2 event) {
  std::cout << "TestEvent2 in State A" << std::endl;
}


void test() {
  StateMachine<StateA, StateB> sm;

  sm.update();
  sm.handle(TestEvent1());
  sm.handle(TestEvent2());
  sm.transition<StateB>();
  sm.update();
  sm.handle(TestEvent2());
  sm.handle(TestEvent1());
  sm.transition<StateA>();
}

}// namespace variadic_simple
#endif//STATE_MACHINES_VARIADIC_SIMPLE_HPP
