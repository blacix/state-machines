#include "classic.hpp"
#include <iostream>
int main() {
  classic::StateMachine classicStateMachine;
  classicStateMachine.onEvent();
  classicStateMachine.onEvent();
  classicStateMachine.onEvent();
  return 0;
}
