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

  virtual void onEvent(StateMachine& stateMachine) {
    std::cout << "onEvent called in wrong state: " << static_cast<int>(mStateID) << std::endl;
  }

  StateId getStateID() const { return mStateID; }

private:
  const StateId mStateID;
};

class StateMachine {
public:
  StateMachine();
  void onEvent();
  void changeState(const StateId stateId);

private:
  StateId mCurrentStateID;
  std::map<StateId, std::unique_ptr<State>> mStates;
};


class StateA : public State {
public:
  StateA()
      : State(StateId::cStateA) {}
  void onEvent(StateMachine& stateMachine) override {
    stateMachine.changeState(StateId::cStateB);
  }
};

class StateB : public State {
public:
  StateB()
      : State(StateId::cStateB) {}
  void onEvent(StateMachine& stateMachine) override {
    stateMachine.changeState(StateId::cStateC);
  }
};

class StateC : public State {
public:
  StateC()
      : State(StateId::cStateC) {}
};

// Implementation of StateMachine methods
StateMachine::StateMachine()
    : mCurrentStateID(StateId::cStateA) {
  mStates[StateId::cStateA] = std::make_unique<StateA>();
  mStates[StateId::cStateB] = std::make_unique<StateB>();
  mStates[StateId::cStateC] = std::make_unique<StateC>();
}

void StateMachine::onEvent() {
  mStates[mCurrentStateID]->onEvent(*this);
}

void StateMachine::changeState(const StateId stateId) {
  std::cout << "changeState from " << static_cast<int>(mCurrentStateID) << " to " << static_cast<int>(stateId) << std::endl;
  mCurrentStateID = stateId;
}


}// namespace classic


#endif//STATE_MACHINES_CLASSIC_HPP
