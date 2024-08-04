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


State1::State1(StateMachine& machine)
    : mStateMachine(machine) {}

template<>
void State1::handle<class TestEvent1>(const TestEvent1& event) {
  std::cout << "Handling TestEvent1 in State1" << std::endl;
  mStateMachine.transition(StateID::cState2);
}

State2::State2(StateMachine& machine)
    : mStateMachine(machine) {}

template<>
void State2::handle<class TestEvent2>(const TestEvent2& event) {
  std::cout << "Handling TestEvent2 in State2" << std::endl;
  mStateMachine.transition(StateID::cState1);
}


int test() {
  StateMachine sm;
  sm.handle(TestEvent1());
  sm.handle(TestEvent2());
  sm.handle(TestEvent2());
  return 0;
}

}// namespace variant_states
