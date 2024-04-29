#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ctime>

std::tm make_tm(int year, int month, int day);
bool isLeapYear(int year);
std::tm string_to_tm(const std::string &date_str);
std::chrono::system_clock::time_point string_to_time_point(const std::string &date_str);
std::tm time_point_to_tm(const std::chrono::system_clock::time_point &time);
std::string time_point_to_string(const std::chrono::system_clock::time_point &time);
double daysBetween(const std::string &date1, const std::string &date2);