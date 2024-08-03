#include "classic.hpp"
#include "template_id.hpp"
#include "template_states.hpp"
#include "variadic_states.hpp"
#include <iostream>
int main() {
  classic::test();
  template_id::test();
  template_states::test();
  variadic_states::test();
  return 0;
}
