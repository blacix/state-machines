#include "classic.hpp"
#include <iostream>
int main() {
  classic::StateMachine classicStateMachine;
  classicStateMachine.onEventB();
  classicStateMachine.onEventB();
  classicStateMachine.onEventC();
  classicStateMachine.onEventA();
  return 0;
}
