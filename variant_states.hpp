// state_machine.hpp
#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <iostream>
#include <map>
#include <memory>
#include <variant>

namespace variant_states {

class StateMachine;// Forward declaration

// Forward declarations of state classes
class State1;
class State2;

// Enum to identify mStates
enum class StateID { cState1,
                     cState2 };

// State machine class declaration
class StateMachine {
public:
  using State = std::variant<std::unique_ptr<State1>, std::unique_ptr<State2>>;

  StateMachine();
  void transition(StateID newState);
  void handle();

private:
  std::map<StateID, State> mStates;
  State *mCurrentState;
};

// State class declarations
class State1 {
public:
  explicit State1(StateMachine& machine);
  void handle();

private:
  StateMachine& machine;
};

class State2 {
public:
  explicit State2(StateMachine& machine);
  void handle();

private:
  StateMachine& machine;
};

// Test function declaration
int test();

}// namespace variant_states

#endif// STATE_MACHINE_HPP