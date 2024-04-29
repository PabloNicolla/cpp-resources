#pragma once

#include <iostream>
#include <optional>
#include <limits>
#include <string>
#include <sstream>

std::optional<int> getNumber(std::istream& in = std::cin);
std::optional<std::string> getLine(std::istream& in = std::cin);
void bufferSafetyCheck(std::istream& in = std::cin);
bool promptToExitLoop(std::istream& in = std::cin);