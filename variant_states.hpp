// state_machine.hpp
#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <iostream>
#include <map>
#include <memory>
#include <variant>

namespace variant_states {

class TestEvent1 {};
class TestEvent2 {};


class StateMachine;// Forward declaration

// Forward declarations of state classes
class State1;
class State2;

// Enum to identify mStates
enum class StateID { cState1,
                     cState2 };

// State mStateMachine class declaration
class StateMachine {
public:
  using State = std::variant<std::unique_ptr<State1>, std::unique_ptr<State2>>;

  StateMachine();
  void transition(StateID newState);
  template<typename EventType>
  void handle(const EventType& event) {
    std::visit([event](auto& state) { state->handle(event); }, *mCurrentState);
  }

private:
  std::map<StateID, State> mStates;
  State *mCurrentState;
};

// State class declarations
class State1 {
public:
  explicit State1(StateMachine& machine);

  template<typename EventType>
  void handle(const EventType& event) {
    std::cout << "Unhandled event in State1" << std::endl;
  }

private:
  StateMachine& mStateMachine;
};

class State2 {
public:
  explicit State2(StateMachine& machine);

  template<typename EventType>
  void handle(const EventType& event) {
    std::cout << "Unhandled event in State1" << std::endl;
  }

private:
  StateMachine& mStateMachine;
};

// Test function declaration
int test();

}// namespace variant_states

#endif// STATE_MACHINE_HPP