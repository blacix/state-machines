#include "classic.hpp"
#include "template_events.hpp"
#include "template_id.hpp"
#include "template_states.hpp"
#include "variadic_states.hpp"
int main() {
  classic::test();
  template_id::test();
  template_states::test();
  variadic_states::test();
  template_events::test();
  return 0;
}
