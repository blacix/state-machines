#include "simple.hpp"
#include "template_events.hpp"
#include "template_id.hpp"
#include "variadic_enhanced.hpp"
#include "variadic_flexible.hpp"
#include "variadic_simple.hpp"

int main() {
  simple::test();
  template_id::test();
  variadic_simple::test();
  variadic_enhanced::test();
  variadic_flexible::test();
  template_events::test();
  return 0;
}
