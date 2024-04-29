#include "run_tests.h"

#if RUN_TESTS == 1
#include <doctest/doctest.h>
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ctime>
#include "date.h"

/// @brief makes a tm structure representing a date
/// @param year years since 1900
/// @param month months since January - [0, 11]
/// @param day day of the month - [1, 31]
std::tm make_tm(int year, int month, int day)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    return tm;
}

/// @brief checks for leap year
/// @return true if leap year, false otherwise
bool is_leap_year(int year)
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

/// @brief converts a string to a tm structure. Format `dd/mm/yyyy`
std::tm string_to_tm(const std::string &date_str)
{
    constexpr int monthDay[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
    std::tm tm = {};
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "%d/%m/%Y");
    if (!is_leap_year(tm.tm_year + 1900) || tm.tm_mon != 1)
    {
        if (monthDay[tm.tm_mon] < tm.tm_mday)
        {
            tm = {};
        }
    }
    else
    {
        if (monthDay[tm.tm_mon] + 1 < tm.tm_mday)
        {
            tm = {};
        }
    }
    return tm;
}

/// @brief converts a string to a time_point. Format `dd/mm/yyyy`
std::chrono::system_clock::time_point string_to_time_point(const std::string &date_str)
{
    auto tm = string_to_tm(date_str);
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

/// @brief converts time_point to a tm structure
std::tm time_point_to_tm(const std::chrono::system_clock::time_point &time)
{
    std::time_t time_t = std::chrono::system_clock::to_time_t(time);
    std::tm tm;
    localtime_s(&tm, &time_t);
    return tm;
}

/// @brief converts a time_point to a string
std::string time_point_to_string(const std::chrono::system_clock::time_point &time)
{
    auto tm = time_point_to_tm(time);
    std::ostringstream ss;
    ss << std::put_time(&tm, "%d/%m/%Y");
    return ss.str();
}

/// @brief gets days between two strings. Format `dd/mm/yyyy`
/// @param date1 to date
/// @param date2 from date
/// @return days passed from date2 to date1
double days_between(const std::string &date1, const std::string &date2)
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

/// @brief get years between two strings. Format `dd/mm/yyyy`
/// Important: the end date is not included in calculation
/// @param date1 to date
/// @param date2 from date
/// @return full years passed from date2 to date1
int years_between(const std::string &date1, const std::string &date2)
{
    int yearsBetween{};
    auto d1Tm = string_to_tm(date1);
    auto d2Tm = string_to_tm(date2);
    auto daysBetween = days_between(date1, date2);

    if (static_cast<int>(daysBetween) == 0)
    {
        yearsBetween = 0;
    }
    else if (daysBetween < 0)
    {
        tm temp = d1Tm;
        d1Tm = d2Tm;
        d2Tm = temp;
    }

    int currYear = d1Tm.tm_year + 1900;
    if (is_leap_year(currYear) && (d1Tm.tm_mon > 1))
    {
        --daysBetween;
    }
    --currYear;
    for (int i{d1Tm.tm_year - d2Tm.tm_year}; i > 0; --i)
    {
        if (is_leap_year(currYear))
        {
            if (i != 1)
            {
                --daysBetween;
            }
            else if (d2Tm.tm_mon <= 1)
            {
                --daysBetween;
            }
        }
        --currYear;
    }
    yearsBetween = static_cast<int>(daysBetween / 365);

    if (static_cast<int>(daysBetween) % 365 == 0)
    {
        if (d2Tm.tm_mday == 29 && d2Tm.tm_mon == 1)
        {
            // do nothing
        }
        else if (d1Tm.tm_mday != d2Tm.tm_mday)
        {
            --yearsBetween;
        }
    }

    return yearsBetween;
}

#if RUN_TESTS == 1

// ---------------------------------------------------------- Testing is_leap_year ----------------------------------------------------------

TEST_CASE("is_leap_year - suit 1")
{
    // Test cases for leap years
    CHECK(is_leap_year(2000) == true);
    CHECK(is_leap_year(2020) == true);
    CHECK(is_leap_year(2024) == true);

    // Test cases for non-leap years
    CHECK(is_leap_year(1900) == false);
    CHECK(is_leap_year(2001) == false);
    CHECK(is_leap_year(2100) == false);
}

// ---------------------------------------------------------- Testing string_to_tm ----------------------------------------------------------

TEST_CASE("string_to_tm - suit 1")
{
    // Valid date: 01/01/2020
    std::string valid_date = "01/01/2020";
    std::tm result = string_to_tm(valid_date);
    CHECK(result.tm_year == 120); // 2020 - 1900
    CHECK(result.tm_mon == 0);    // January
    CHECK(result.tm_mday == 1);   // 1st day of the month
}

TEST_CASE("string_to_tm - suit 2")
{
    // Invalid date: 31/04/2024 (April has 30 days)
    std::string invalid_date = "31/04/2024";
    std::tm result = string_to_tm(invalid_date);
    CHECK(result.tm_year == 0); // Invalid year
    CHECK(result.tm_mon == 0);  // Invalid month
    CHECK(result.tm_mday == 0); // Invalid day
}

TEST_CASE("string_to_tm - suit 3")
{
    // Leap year: 29/02/2024 (valid)
    std::string leap_year_date = "29/02/2024";
    std::tm result_leap = string_to_tm(leap_year_date);
    CHECK(result_leap.tm_year == 124); // 2024 - 1900
    CHECK(result_leap.tm_mon == 1);    // February
    CHECK(result_leap.tm_mday == 29);  // 29th day of the month

    // Non-leap year: 29/02/2021 (invalid)
    std::string non_leap_year_date = "29/02/2021";
    std::tm result_non_leap = string_to_tm(non_leap_year_date);
    CHECK(result_non_leap.tm_year == 0); // Invalid year
    CHECK(result_non_leap.tm_mon == 0);  // Invalid month
    CHECK(result_non_leap.tm_mday == 0); // Invalid day
}

// ---------------------------------------------------------- Testing days_between ----------------------------------------------------------

TEST_CASE("days_between - suit 1")
{
    // Valid date range: 01/01/2020 to 01/02/2020 (31 days)
    std::string date1 = "01/02/2020";
    std::string date2 = "01/01/2020";
    double result = days_between(date1, date2);
    CHECK(static_cast<int>(result) == 31);
}

TEST_CASE("days_between - suit 2")
{
    // Negative date range: 01/01/2020 to 01/02/2020 (reversed order)
    std::string date1 = "01/01/2020";
    std::string date2 = "01/02/2020";
    double result = days_between(date1, date2);
    CHECK(static_cast<int>(result) == -31.0);
}

TEST_CASE("days_between - suit 3")
{
    // Same date: 15/03/2021 to 15/03/2021 (0 days)
    std::string same_date = "15/03/2021";
    double result_same = days_between(same_date, same_date);
    CHECK(static_cast<int>(result_same) == 0);
}

TEST_CASE("days_between - suit 4")
{
    // Leap year: 29/02/2024 to 01/03/2024 (2 days)
    std::string leap_year_date1 = "29/02/2024";
    std::string leap_year_date2 = "01/03/2024";
    double result_leap = days_between(leap_year_date1, leap_year_date2);
    CHECK(static_cast<int>(result_leap) == -1);
}

// ---------------------------------------------------------- Testing years_between ----------------------------------------------------------

TEST_CASE("years_between - suit 1")
{
    // Valid date range: 01/01/2020 to 01/01/2024 (4 years)
    int result = years_between("01/01/2024", "01/01/2020");
    CHECK(result == 4);
}

TEST_CASE("years_between - suit 2")
{
    // Negative date range: 01/01/2020 to 01/01/2024 (reversed order)
    int result = years_between("01/01/2020", "01/01/2024");
    CHECK(result == -4);
}

TEST_CASE("years_between - suit 3")
{
    // Same date: 15/03/2021 to 15/03/2021 (0 years)
    int result_same = years_between("15/03/2021", "15/03/2021");
    CHECK(result_same == 0);
}

TEST_CASE("years_between - suit 4")
{
    // --- one leap years

    // 1 year excluding the end date. Total 366 days
    int result_leap = years_between("29/02/2024", "28/02/2023");
    CHECK(result_leap == 1);

    // 11 months, 28 days excluding the end date. Total 365 days
    result_leap = years_between("29/02/2024", "01/03/2023");
    CHECK(result_leap == 0);

    // 1 year excluding the end date. Total 366 days
    result_leap = years_between("01/03/2024", "01/03/2023");
    CHECK(result_leap == 1);

    // 1 year excluding the end date. Total 366 days
    result_leap = years_between("28/02/2024", "28/02/2023");
    CHECK(result_leap == 1);

    // --- two leap years

    // 4 years excluding the end date. Total 1461 days
    result_leap = years_between("29/02/2024", "29/02/2020");
    CHECK(result_leap == 4);

    // 4 years excluding the end date. Total 1461 days
    result_leap = years_between("28/02/2024", "28/02/2020");
    CHECK(result_leap == 4);

    // 4 years excluding the end date. Total 1461 days
    result_leap = years_between("01/03/2024", "01/03/2020");
    CHECK(result_leap == 4);

    // 3 years, 11 months, 28 days excluding the end date. Total 1460 days
    result_leap = years_between("29/02/2024", "01/03/2020");
    CHECK(result_leap == 3);

    // 4 years, 1 day excluding the end date. Total 1462 days
    result_leap = years_between("01/03/2024", "29/02/2020");
    CHECK(result_leap == 4);

    // --- Random

    // 44 years, 1 day excluding the end date. Total 16,072 days
    result_leap = years_between("01/03/2024", "29/02/1980");
    CHECK(result_leap == 44);

    // 44 years excluding the end date. Total 16,071 days
    result_leap = years_between("29/02/2024", "29/02/1980");
    CHECK(result_leap == 44);

    // 43 years, 11 months, 28 days excluding the end date. Total 16,070 days
    result_leap = years_between("29/02/2024", "01/03/1980");
    CHECK(result_leap == 43);
}

#endif