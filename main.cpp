#include "classic.hpp"
#include "template_events.hpp"
#include "template_id.hpp"
#include "template_states.hpp"
#include <iostream>
int main() {
  classic::test();
  template_id::test();
  template_states::test();
  template_events::test();
  return 0;
}
