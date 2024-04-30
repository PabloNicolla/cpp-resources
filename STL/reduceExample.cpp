#include <numeric>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <execution>
#include <unordered_map>
#include "reduceExample.h"

void reduceExample()
{
  std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::unordered_map<std::string, int> m1{

      {"k1", 1}, {"k2", 2}, {"k3", 3}, {"k4", 4}, {"k5", 5}};
  auto ret1 = std::reduce(std::execution::seq, v1.begin(), v1.end(), 0, [](const int value1, const auto value2)
                          { return value1 + value2; });
  std::cout << ret1 << "\n\n";

  auto ret2 = std::reduce(std::execution::seq, m1.begin(), m1.end(), 0, [](const int value1, const auto &value2)
                          { return value1 + value2.second; });
  std::cout << ret2 << "\n\n";

  auto ret3 = std::reduce(std::execution::seq, m1.begin(), m1.end(), std::string(""), [](const auto &value1, const auto &value2)
                          { return value1 + value2.first; });
  std::cout << ret3 << "\n\n";
}
