#include "grtp.hpp"
#include "simple.hpp"
#include "template_id.hpp"
#include "variadic.hpp"
#include "variadic_enhanced.hpp"
#include "variadic_flexible.hpp"
#include "variadic_simple.hpp"
#include "variant_states.hpp"


int main() {
  simple::test();
  template_id::test();
  variant_states::test();
  variadic_simple::test();
  variadic_enhanced::test();
  variadic_flexible::test();
  grtp::test();
  variadic::test();
  return 0;
}
