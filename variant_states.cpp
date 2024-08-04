#include "variant_states.hpp"

namespace variant_states {

StateMachine::StateMachine() {
  mStates[StateID::cState1] = std::make_unique<State1>(*this);
  mStates[StateID::cState2] = std::make_unique<State2>(*this);
  mCurrentState = &mStates[StateID::cState1];
}

void StateMachine::transition(StateID newState) {
  mCurrentState = &mStates[newState];
}

void StateMachine::handle() {
  std::visit([](auto& state_ptr) { state_ptr->handle(); }, *mCurrentState);
}

State1::State1(StateMachine& machine)
    : machine(machine) {}
void State1::handle() {
  std::cout << "Handling State1" << std::endl;
  machine.transition(StateID::cState2);
}

State2::State2(StateMachine& machine)
    : machine(machine) {}
void State2::handle() {
  std::cout << "Handling State2" << std::endl;
  machine.transition(StateID::cState1);
}


int test() {
  StateMachine sm;
  sm.handle();
  sm.handle();
  sm.handle();
  return 0;
}

}// namespace variant_states
