
#ifndef STATE_MACHINES_VARIADIC_ENHANCED_HPP
#define STATE_MACHINES_VARIADIC_ENHANCED_HPP
#include <functional>
#include <iostream>
#include <tuple>
#include <variant>

namespace variadic_enhanced {

template<typename... States>
class StateMachine {
public:
  template<typename State>
  void changeState() {
    mCurrentState = &std::get<State>(mStates);
  }

  template<typename Event>
  void handle(const Event& event) {
    auto passEventToState = [this, &event](auto statePtr) {
      statePtr->handle(*this, event);
    };
    std::visit(passEventToState, mCurrentState);
  }

private:
  std::tuple<States...> mStates;
  std::variant<States *...> mCurrentState{&std::get<0>(mStates)};
};

struct OpenEvent {};
struct CloseEvent {};

struct ClosedState;
struct OpenState;

struct ClosedState {
  template<typename Machine>
  void handle(Machine& machine, const OpenEvent&) const {
    std::cout << "Opening the door..." << std::endl;
    machine.template changeState<OpenState>();
  }

  template<typename Machine>
  void handle(Machine&, const CloseEvent&) const {
    std::cout << "Cannot close. The door is already closed!" << std::endl;
  }
};

struct OpenState {
  template<typename Machine>
  void handle(Machine&, const OpenEvent&) const {
    std::cout << "Cannot open. The door is already open!" << std::endl;
  }

  template<typename Machine>
  void handle(Machine& machine, const CloseEvent&) const {
    std::cout << "Closing the door..." << std::endl;
    machine.template changeState<ClosedState>();
  }
};

using Door = StateMachine<ClosedState, OpenState>;

int test() {
  Door door;

  door.handle(OpenEvent{});
  door.handle(CloseEvent{});

  door.handle(CloseEvent{});
  door.handle(OpenEvent{});

  return 0;
}

}// namespace variadic_enhanced

#endif//STATE_MACHINES_VARIADIC_ENHANCED_HPP
