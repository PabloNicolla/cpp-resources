#include "run_tests.h"

#if RUN_TESTS == 1
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#endif

#include "date.h"

#if RUN_TESTS != 1

// Example usage
int main()
{
}

#endif