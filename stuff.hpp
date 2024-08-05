#ifndef STATE_MACHINES_STUFF_HPP
#define STATE_MACHINES_STUFF_HPP
#include <iostream>
#include <map>
#include <memory>
#include <variant>

namespace stuff {

// Enum to identify mStates
enum class StateId { cState1,
                     cState2 };


class StateMachine;// Forward declaration

template<typename StateIdType>
class State {
public:
  virtual StateIdType getId() const = 0;
  virtual void update(StateMachine& stateMachine) = 0;
};

class State1 : public State<StateId> {
public:
  StateId getId() const override { return StateId::cState1; }
  void update(StateMachine& stateMachine) override;
};

class State2 : public State<StateId> {

public:
  StateId getId() const override { return StateId::cState2; }
  void update(StateMachine& stateMachine) override;
};


// State mStateMachine class declaration

class StateMachine {
public:
  StateMachine() {
    addStates<State1, State2>();
    mCurrentStatePointer = mStates[typeid(State1).hash_code()].get();
  }

private:
  template<typename... States>
  void addStates() {
    (mStates.emplace(typeid(States).hash_code(), std::make_unique<States>()), ...);
  }

public:
  // transition with ID
  void transition(StateId newState) {
    mCurrentStateId = newState;
  }

  template<typename StateType>
  void transition() {
    std::cout << "transition to " << typeid(StateType).name() << std::endl;
    mCurrentStateId = mStates[typeid(StateType).hash_code()]->getId();
    mCurrentStatePointer = mStates[typeid(StateType).hash_code()].get();
  }

  void update() {
    mCurrentStatePointer->update(*this);
  }

  void work() {
  }


private:
  // used when transition is called with the StateID
  std::map<size_t, std::unique_ptr<State<StateId>>> mStates;
  // used when transition is called State template parameter
  StateId mCurrentStateId = StateId::cState1;
  State<StateId> *mCurrentStatePointer = nullptr;
};


// implementation

void State1::update(stuff::StateMachine& stateMachine) {
  std::cout << "update State1 " << std::endl;
  stateMachine.work();
  stateMachine.transition<State2>();
}

void State2::update(stuff::StateMachine& stateMachine) {
  std::cout << "update State2 " << std::endl;
  stateMachine.work();
  stateMachine.transition<State1>();
}


int test() {
  StateMachine sm;
  sm.update();
  sm.update();

  return 0;
}
}// namespace stuff

#endif//STATE_MACHINES_STUFF_HPP
