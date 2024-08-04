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
  using State = std::variant<State1, State2>;

  StateMachine();
  void transition(StateID newState);
  template<typename EventType>
  void handle(const EventType& event) {
    std::visit([this, event](auto& state) { state.handle(event, *this); }, *mCurrentState);
  }

private:
  std::map<StateID, State> mStates;
  State *mCurrentState;
};


// If stats are not default constructable, cannot be stored in a variant.
// States could have a reference to the StateMachine initialized in their constructor, but due to the above,
// the state machine is passed to the handle methods.
// Another solution would be to store the variants in a pointer.
// State class declarations
class State1 {
public:
  State1() = default;
  State1(const State1&) = default;
  State1(State1&&) = default;
  State1& operator=(const State1&) = default;
  State1& operator=(State1&&) = default;
  ~State1() = default;

  template<typename EventType>
  void handle(const EventType& event, StateMachine& machine) {
    std::cout << "Unhandled event in State1" << std::endl;
  }
};

class State2 {
public:
  State2() = default;
  State2(const State2&) = default;
  State2(State2&&) = default;
  State2& operator=(const State2&) = default;
  State2& operator=(State2&&) = default;
  ~State2() = default;

  template<typename EventType>
  void handle(const EventType& event, StateMachine& machine) {
    std::cout << "Unhandled event in State1" << std::endl;
  }
};

// Test function declaration
int test();

}// namespace variant_states

#endif// STATE_MACHINE_HPP