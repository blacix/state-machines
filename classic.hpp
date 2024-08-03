#ifndef STATE_MACHINES_CLASSIC_HPP
#define STATE_MACHINES_CLASSIC_HPP
#include <iostream>
#include <map>
#include <memory>

namespace classic {

enum class StateId {
  cStateA,
  cStateB,
  cStateC
};

class StateMachine;
class State;


class State {
public:
  explicit State(const StateId stateId)
      : mStateID(stateId) {}

  virtual void enter(StateMachine& stateMachine) {}

  virtual void onEventA(StateMachine& stateMachine) {
    std::cout << "onEventA called in wrong state: " << static_cast<int>(mStateID) << std::endl;
  }

  virtual void onEventB(StateMachine& stateMachine) {
    std::cout << "onEventB called in wrong state: " << static_cast<int>(mStateID) << std::endl;
  }

  virtual void onEventC(StateMachine& stateMachine) {
    std::cout << "onEventC called in wrong state: " << static_cast<int>(mStateID) << std::endl;
  }

  virtual void leave(StateMachine& stateMachine) {}

  StateId getStateID() const { return mStateID; }

private:
  const StateId mStateID;
};

class StateMachine {
public:
  StateMachine();
  void onEventA();
  void onEventB();
  void onEventC();
  void changeState(const StateId stateId);

  void doSomething();

private:
  StateId mCurrentStateID;
  std::map<StateId, std::unique_ptr<State>> mStates;
};


class StateA : public State {
public:
  StateA()
      : State(StateId::cStateA) {}
  void onEventA(StateMachine& stateMachine) override {
    // do nothing
  }

  void onEventB(StateMachine& stateMachine) override {
    stateMachine.doSomething();
    stateMachine.changeState(StateId::cStateB);
  }
};

class StateB : public State {
public:
  StateB()
      : State(StateId::cStateB) {}
  void onEventC(StateMachine& stateMachine) override {
    stateMachine.changeState(StateId::cStateC);
  }
};

class StateC : public State {
public:
  StateC()
      : State(StateId::cStateC) {}

  void onEventA(StateMachine& stateMachine) override {
    stateMachine.changeState(StateId::cStateA);
  }
};

// Implementation of StateMachine methods
StateMachine::StateMachine()
    : mCurrentStateID(StateId::cStateA) {
  mStates[StateId::cStateA] = std::make_unique<StateA>();
  mStates[StateId::cStateB] = std::make_unique<StateB>();
  mStates[StateId::cStateC] = std::make_unique<StateC>();
}

void StateMachine::onEventA() {
  mStates[mCurrentStateID]->onEventA(*this);
}

void StateMachine::onEventB() {
  mStates[mCurrentStateID]->onEventB(*this);
}

void StateMachine::onEventC() {
  mStates[mCurrentStateID]->onEventC(*this);
}

void StateMachine::changeState(const StateId stateId) {
  mStates[mCurrentStateID]->leave(*this);
  std::cout << "changeState from " << static_cast<int>(mCurrentStateID) << " to " << static_cast<int>(stateId) << std::endl;
  mCurrentStateID = stateId;
  mStates[mCurrentStateID]->enter(*this);
}

void StateMachine::doSomething() {
  std::cout << "something is done" << std::endl;
}

void test() {
  classic::StateMachine classicStateMachine;
  classicStateMachine.onEventB();
  classicStateMachine.onEventB();
  classicStateMachine.onEventC();
  classicStateMachine.onEventA();
}

}// namespace classic


#endif//STATE_MACHINES_CLASSIC_HPP
