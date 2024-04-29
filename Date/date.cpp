#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ctime>

// Make a tm structure representing a date
std::tm make_tm(int year, int month, int day)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900; // Years count from 1900
    tm.tm_mon = month - 1;    // Months count from January=0
    tm.tm_mday = day;         // Days count from 1
    return tm;
}

// check if leap year
bool isLeapYear(int year)
{
    if (year % 4 != 0)
    {
        return false;
    }
    else if (year % 100 != 0)
    {
        return true;
    }
    else if (year % 400 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Convert a string to a tm structure
std::tm string_to_tm(const std::string &date_str)
{
    constexpr int monthDay[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
    std::tm tm = {};
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "%d/%m/%Y");
    if (!isLeapYear(tm.tm_year + 1900) || tm.tm_mon != 1)
    {
        if (monthDay[tm.tm_mon] < tm.tm_mday)
        {
            tm = {};
        }
    }
    else
    {
        if (monthDay[tm.tm_mon] < tm.tm_mday + 1)
        {
            tm = {};
        }
    }
    return tm;
}

// Convert a string to a time_point
std::chrono::system_clock::time_point string_to_time_point(const std::string &date_str)
{
    auto tm = string_to_tm(date_str);
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

// Convert time_point to a tm structure
std::tm time_point_to_tm(const std::chrono::system_clock::time_point &time)
{
    std::time_t time_t = std::chrono::system_clock::to_time_t(time);
    std::tm tm;
    localtime_s(&tm, &time_t); // Use localtime_s instead of localtime
    return tm;
}

// Convert a time_point to a string
std::string time_point_to_string(const std::chrono::system_clock::time_point &time)
{
    auto tm = time_point_to_tm(time);
    std::ostringstream ss;
    ss << std::put_time(&tm, "%d/%m/%Y");
    return ss.str();
}

// Get days between two strings
double daysBetween(const std::string &date1, const std::string &date2)
{
    // Structures representing the two dates
    std::tm tm1 = string_to_tm(date1);
    std::tm tm2 = string_to_tm(date2);

    // Convert to time_t (seconds since 1970-01-01 00:00:00 UTC)
    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);

    // Calculate the difference in days
    const int seconds_per_day = 60 * 60 * 24;

    // To be fully portable, use difftime to get the difference in seconds:
    return std::difftime(time1, time2) / seconds_per_day;
}