#include "run_tests.h"

#if RUN_TESTS == 1
#include <doctest/doctest.h>
#endif

#include <string>
#include "Trim.h"

/// @brief Left trim the string based on the delimiters
std::string l_trim(const std::string& str, const std::string& delimiters)
{
  const auto strBegin = str.find_first_not_of(delimiters);
  if (strBegin == std::string::npos)
  {
    return "";
  }
  return str.substr(strBegin);
}

/// @brief Right trim the string based on the delimiters
std::string r_trim(const std::string& str, const std::string& delimiters)
{
  const auto strEnd = str.find_last_not_of(delimiters);
  if (strEnd == std::string::npos)
  {
    return "";
  }
  return str.substr(0, strEnd + 1);
}

/// @brief Trim the string based on the delimiters
std::string trim(const std::string& str, const std::string& delimiters)
{
  const auto strBegin = str.find_first_not_of(delimiters);
  if (strBegin == std::string::npos)
  {
    return "";
  }
  const auto strEnd = str.find_last_not_of(delimiters);
  const auto strRange = strEnd - strBegin + 1;
  return str.substr(strBegin, strRange);
}

#if RUN_TESTS == 1

TEST_CASE("ltrim - suit 1")
{
  CHECK(l_trim("  abc", " ") == "abc");
  CHECK(l_trim("abc", " ") == "abc");
  CHECK(l_trim("  ", " ") == "");
  CHECK(l_trim("", " ") == "");
}

TEST_CASE("rtrim - suit 1")
{
  CHECK(r_trim("abc  ", " ") == "abc");
  CHECK(r_trim("abc", " ") == "abc");
  CHECK(r_trim("  ", " ") == "");
  CHECK(r_trim("", " ") == "");
}

TEST_CASE("trim - suit 1")
{
  CHECK(trim("  abc  ", " ") == "abc");
  CHECK(trim("abc", " ") == "abc");
  CHECK(trim("  ", " ") == "");
  CHECK(trim("", " ") == "");
}

#endif
