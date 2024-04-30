#include "run_tests.h"

#if RUN_TESTS == 1
#include <doctest/doctest.h>
#endif

#include <string>
#include "replaceIf.h"

void replaceAll(std::string &str, const std::string &toFind, const std::string &toReplace)
{
  std::string::size_type index = 0;
  while ((index = str.find(toFind, index)) != std::string::npos)
  {
    str.replace(index, toFind.size(), toReplace);
  }
}

#if RUN_TESTS == 1
TEST_CASE("replaceAll - suit 1")
{
  std::string str = "abc";
  replaceAll(str, "a", "b");
  CHECK(str == "bbc");
  replaceAll(str, "b", "c");
  CHECK(str == "ccc");
  replaceAll(str, "c", "d");
  CHECK(str == "ddd");
  replaceAll(str, "d", "e");
  CHECK(str == "eee");
}

TEST_CASE("replaceAll - suit 2")
{
  std::string str = "line1\\nline2\\nline3\\n";
  replaceAll(str, "\\n", "\n");
  CHECK(str == "line1\nline2\nline3\n");
  replaceAll(str, "line", "block");
  CHECK(str == "block1\nblock2\nblock3\n");
  replaceAll(str, "block1\n", "");
  CHECK(str == "block2\nblock3\n");
  replaceAll(str, "block3\n", "");
  CHECK(str == "block2\n");
}

TEST_CASE("replaceAll - suit 3")
{
  std::string str = "A random line";
  replaceAll(str, "z", "abc");
  CHECK(str == "A random line");
}
#endif