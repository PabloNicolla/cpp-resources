#include "run_tests.h"

#if RUN_TESTS == 1
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#endif

#if RUN_TESTS != 1

#include "readFile_multithread.h"

int main()
{
  processFile();
}

#endif
