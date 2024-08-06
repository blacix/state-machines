#ifndef STATE_MACHINES_VARIADIC_HPP
#define STATE_MACHINES_VARIADIC_HPP

#include <variant>

namespace variadic {


// Template class for composing an overloaded function-like object out of lambda expressions
template<typename... Fs>
struct overload : Fs... {
  using Fs::operator()...;
};

// Constructor deduction guide to eliminate the need for specifying template arguments; they get deduced from constructor arguments
template<typename... Fs>
overload(Fs...) -> overload<Fs...>;


// Serves as a 'compile-time pair', to store state name - state implementation pairs. By defining it
// as an incomplete type, it imposes no further substitution work --> reduced compilation time
template<typename StateName, template<typename> typename StateClass>
struct State;


// Dynamic state machine class template; accepts a list of states.
template<typename... States>
class StateMachine;

template<typename... StateName, template<typename> typename... StateClass>
class StateMachine<State<StateName, StateClass>...>
    : StateClass<std::variant<StateName...>>... {

  // Return type for the state functions; gets passed as template argument to each StateClass
  typedef std::variant<StateName...> state_result_t;

  state_result_t current;

public:
  // Calls the state defined in 'current'. If there are multiple states with the same name, the function call below will result in
  // an error due to ambiguity during overload resolution
  template<typename... Ts>
  void operator()(Ts&&...args) {
    current =
        std::visit(overload{([&](StateName) -> state_result_t { return StateClass<state_result_t>::operator()(std::forward<Ts>(args)...); })...}, current);
  }
};


template<typename R>
struct state_1 {
  template<typename... Ts>
  R operator()(Ts&&...) {
    std::cout << "state 1" << std::endl;
    return std::integral_constant<int, 2>{};
  }
};

template<typename R>
struct state_2 {
  template<typename... Ts>
  R operator()(Ts&&...) {
    std::cout << "state 2" << std::endl;
    return std::integral_constant<int, 1>{};
  }
};


int test() {
  StateMachine<State<std::integral_constant<int, 1>, state_1>, State<std::integral_constant<int, 2>, state_2>> dsm;

  dsm(1, 2, 3);
  dsm(1, 2, 3);
  dsm(1, 2, 3);
  dsm(1, 2, 3);
  return 0;
}

}// namespace variadic

#endif