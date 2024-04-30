#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>
#include "merge&removeIfh.h"

void mergeAndRemoveIf() {

  std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  std::vector<int> v2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


  std::vector<int> v3{};
  v3.resize(v1.size() + v2.size());
  std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
  // or
  std::vector<int> v4{};
  std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v4));

  for (const auto& item : v4) {
    std::cout << item << ", ";
  }
  std::cout << "\n\n";


  auto newEnd = std::remove_if(v4.begin(), v4.end(), [](const int v1) { return v1 % 2 == 1; });
  v4.erase(newEnd, v4.end());

  for (const auto& item : v4) {
    std::cout << item << ", ";
  }
  std::cout << "\n\n";
}