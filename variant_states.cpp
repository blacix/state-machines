#include "variant_states.hpp"

namespace variant_states {

StateMachine::StateMachine() {
  mStates[StateID::cState1] = State1();
  mStates[StateID::cState2] = State2();
  mCurrentState = &mStates[StateID::cState1];
}

void StateMachine::transition(StateID newState) {
  mCurrentState = &mStates[newState];
}


template<>
void State1::handle<class TestEvent1>(const TestEvent1& event, StateMachine& machine) {
  std::cout << "Handling TestEvent1 in State1" << std::endl;
  machine.transition(StateID::cState2);
}

template<>
void State2::handle<class TestEvent2>(const TestEvent2& event, StateMachine& machine) {
  std::cout << "Handling TestEvent2 in State2" << std::endl;
  machine.transition(StateID::cState1);
}


int test() {
  StateMachine sm;
  sm.handle(TestEvent1());
  sm.handle(TestEvent2());
  sm.handle(TestEvent2());
  return 0;
}

}// namespace variant_states
