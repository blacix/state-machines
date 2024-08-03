#ifndef STATE_MACHINES_TEMPLATE_ID_HPP
#define STATE_MACHINES_TEMPLATE_ID_HPP
#include <iostream>
#include <list>
#include <map>
#include <memory>

namespace template_id {

// Forward declaration
template<typename StateIdType>
class StateMachine;

// Base State class
template<typename StateIdType>
class State {
public:
  State(const State&) = delete;
  State(State&&) = delete;
  State& operator=(const State&) = delete;
  State& operator=(State&&) = delete;
  virtual ~State() = default;
  virtual void enter() = 0;
  virtual void exit() = 0;
  virtual void update(StateMachine<StateIdType>& stateMachine) = 0;

  StateIdType getStateId() const { return mStateId; }

protected:
  explicit State(StateIdType id)
      : mStateId(id) {}

  StateIdType mStateId;
};

// State Machine class
template<typename StateIdType>
class StateMachine {
public:
  void addState(std::unique_ptr<State<StateIdType>> state) {
    mStates[state->getStateId()] = std::move(state);
  }

  void setInitialState(StateIdType stateId) {
    mCurrentState = mStates[stateId].get();
    if (mCurrentState) {
      mCurrentState->enter();
    }
  }

  void changeState(StateIdType newStateId) {
    if (mCurrentState) {
      mCurrentState->exit();
    }
    mCurrentState = mStates[newStateId].get();
    if (mCurrentState) {
      mCurrentState->enter();
    }
  }

  void update() {
    if (mCurrentState) {
      mCurrentState->update(*this);
    }
  }

  void doSomeWork() {
    std::cout << "some work is done" << std::endl;
  }

private:
  std::map<StateIdType, std::unique_ptr<State<StateIdType>>> mStates;
  State<StateIdType> *mCurrentState = nullptr;
};

// Example usage
enum class TestStateId {
  cState1,
  cState2,
};

class State1 : public State<TestStateId> {
public:
  State1()
      : State(TestStateId::cState1) {}
  void enter() override { std::cout << "Entering state " << static_cast<int>(mStateId) << std::endl; }
  void exit() override { std::cout << "Exiting state " << static_cast<int>(mStateId) << std::endl; }
  void update(StateMachine<TestStateId>& stateMachine) override {
    std::cout << "Updating state " << static_cast<int>(mStateId) << std::endl;
    stateMachine.doSomeWork();
    stateMachine.changeState(TestStateId::cState2);
  }
};

class State2 : public State<TestStateId> {
public:
  State2()
      : State(TestStateId::cState2) {}
  void enter() override { std::cout << "Entering state " << static_cast<int>(mStateId) << std::endl; }
  void exit() override { std::cout << "Exiting state " << static_cast<int>(mStateId) << std::endl; }
  void update(StateMachine<TestStateId>& stateMachine) override {
    std::cout << "Updating state " << static_cast<int>(mStateId) << std::endl;
    stateMachine.changeState(TestStateId::cState1);
  }
};

void test() {
  StateMachine<TestStateId> stateMachine;

  stateMachine.addState(std::make_unique<State1>());
  stateMachine.addState(std::make_unique<State2>());
  stateMachine.setInitialState(TestStateId::cState1);
  stateMachine.update();
  stateMachine.update();
}

}// namespace template_id

#endif//STATE_MACHINES_TEMPLATE_ID_HPP
