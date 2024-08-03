#include "simple.hpp"
#include "template_events.hpp"
#include "template_id.hpp"
#include "variadic_flexible.hpp"
#include "variadic_simple.hpp"
#include "variadic_states.hpp"

int main() {
  simple::test();
  template_id::test();
  variadic_simple::test();
  variadic_flexible::test();
  variadic_states::test();
  template_events::test();
  return 0;
}
