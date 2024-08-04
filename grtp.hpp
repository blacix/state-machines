#ifndef STATE_MACHINES_GRTP_HPP
#define STATE_MACHINES_GRTP_HPP
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>

namespace grtp {

struct TestEvent1 {};
struct TestEvent2 {};

enum class StateId {
  cState1,
  cState2
};

template<typename Derived>
class State {
public:
  Derived& derived() {
    return *static_cast<Derived *>(this);
  }

  virtual StateId getId() = 0;
  virtual void update() {}

  template<typename EventType>
  void handle(const EventType& event) {
    // Access members of Derived here
    static_cast<Derived *>(this)->handleImpl(event);
  }
};

class State1 : public State<State1> {
public:
  StateId getId() override { return StateId::cState1; }
  void update() override {}
  template<typename EventType>
  void handleImpl(const EventType& eventType) {
    std::cout << "unknown event" << std::endl;
  }
};
template<>
void State1::handleImpl<int>(const int& event) {
  std::cout << "int" << std::endl;
  // ...
}

class State2 : public State<State2> {
public:
  StateId getId() override { return StateId::cState2; }
  void update() override {}
  template<typename EventType>
  void handleImpl(const EventType& eventType) {
    // ...
  }
};


class StateMachine {
public:
  template<class StateType>
  void addState(StateId stateId) {
  }

  template<class StateType>
  void transitionTo() {
    mCurrentState = StateType();
  }

  template<typename EventType>
  void handle(const EventType& event) {
    std::visit([event](auto& state) { state.handle(event); }, mCurrentState);
  }

  void update() {
    std::visit([](auto& state) { state.update(); state.handle(TestEvent1()); state.handle(1); }, mCurrentState);
  }

private:
  std::variant<State1, State2> mCurrentState = State1();
};

void test() {
  StateMachine stateMachine;
  stateMachine.update();
  stateMachine.handle(TestEvent2());
}
}// namespace grtp

#endif//STATE_MACHINES_GRTP_HPP
