
#ifndef STATE_MACHINES_VARIADIC_SIMPLE_HPP
#define STATE_MACHINES_VARIADIC_SIMPLE_HPP
#include <functional>
#include <iostream>
#include <tuple>
#include <variant>

namespace variadic_simple {

template<typename... States>
class StateMachine {
public:
  template<typename State>
  void changeState() {
    currentState = &std::get<State>(states);
  }

  template<typename Event>
  void handle(const Event& event) {
    auto passEventToState = [this, &event](auto statePtr) {
      statePtr->handle(*this, event);
    };
    std::visit(passEventToState, currentState);
  }

private:
  std::tuple<States...> states;
  std::variant<States *...> currentState{&std::get<0>(states)};
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

}// namespace variadic_simple

#endif//STATE_MACHINES_VARIADIC_SIMPLE_HPP
