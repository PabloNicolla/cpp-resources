#include "run_tests.h"

#if RUN_TESTS == 1
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#endif

#include "Trim.h"
#include "GetInput.h"

#if RUN_TESTS != 1

int main() {
  return 0;
}

#endif
