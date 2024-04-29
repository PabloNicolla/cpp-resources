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
    std::vector<std::string> dates = {"01/01/2010", "01/01/2020", "01/01/2030"};

    auto aa = string_to_time_point("31/04/2024");
    aa = string_to_time_point("30/04/2024");

    // Search by date
    auto it = std::find(dates.begin(), dates.end(), "01/01/2020");
    if (it != dates.end())
    {
        std::cout << "Date found: " << *it << '\n';
    }

    // Convert between string and time_point
    std::string date_str = "01/01/2020";
    auto date_tp = string_to_time_point(date_str);
    std::cout << "Converted time_point to string: " << time_point_to_string(date_tp) << '\n';
    return 0;
}

#endif