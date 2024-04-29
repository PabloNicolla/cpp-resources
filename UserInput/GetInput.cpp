#include "run_tests.h"

#if RUN_TESTS == 1
#include <doctest/doctest.h>
#endif

#include <iostream>
#include <optional>
#include <limits>
#include <string>
#include <sstream>
#include "GetInput.h"

/// @brief Get a number from the user
std::optional<int> getNumber(std::istream& in /*= std::cin*/)
{
  int number;
  in >> number;

  char nextChar;
  while (in.get(nextChar))
  {
    if (nextChar == '\n')
    {
      break;
    }
    if (!isspace(nextChar))
    {
      in.setstate(std::ios_base::failbit);
      break;
    }
  }

  if (in.fail())
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Please enter a number.\n";
    return {};
  }
  return { number };
}

/// @brief Get a line of text from the user
std::optional<std::string> getLine(std::istream& in /*= std::cin*/)
{
  std::string buff{};
  std::getline(in, buff);

  if (in.fail())
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::clog << "ERROR: Utils::getLine() \n\n";
    return {};
  }
  return { buff };
}

/// @brief Clear the input buffer
void bufferSafetyCheck(std::istream& in /*= std::cin*/)
{
  if (in.rdbuf()->in_avail() > 0)
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::clog << "ERROR: Utils::bufferSafetyCheck() \n\n";
  }
}

/// @brief Prompt the user to exit a loop
bool promptToExitLoop(std::istream& in /*= std::cin*/)
{
  std::cout << "Do you want to cancel/exit this operation? (y/N): ";
  std::string buff = getLine(in).value_or("");
  return buff == "y" || buff == "Y";
}

#if RUN_TESTS == 1

TEST_CASE("getNumber")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "42\n" };
  auto result = getNumber(in);
  REQUIRE(result.has_value());
  CHECK(result.value() == 42);
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("getNumber - invalid input")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "42.5\n" };
  auto result = getNumber(in);
  CHECK(!result.has_value());
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("getNumber - invalid input")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "42 5\n" };
  auto result = getNumber(in);
  CHECK(!result.has_value());
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("getLine")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "Hello, World!\n" };
  auto result = getLine(in);
  REQUIRE(result.has_value());
  CHECK(result.value() == "Hello, World!");
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("getLine - invalid input")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "Hello, World!\n" };
  in.setstate(std::ios_base::failbit);
  auto result = getLine(in);
  CHECK(!result.has_value());
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("bufferSafetyCheck")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "Hello, World!\n" };
  bufferSafetyCheck(in);
  CHECK(in.rdbuf()->in_avail() == 0);
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("promptToExitLoop")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "y\n" };
  CHECK(promptToExitLoop(in));
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("promptToExitLoop")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "Y\n" };
  CHECK(promptToExitLoop(in));
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("promptToExitLoop")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "n\n" };
  CHECK(!promptToExitLoop(in));
  std::cout.rdbuf(oldCoutStreamBuf);
}

TEST_CASE("promptToExitLoop")
{
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(0);
  std::istringstream in{ "N\n" };
  CHECK(!promptToExitLoop(in));
  std::cout.rdbuf(oldCoutStreamBuf);
}

#endif
