#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include "sort&copyIf.h"

void copyAndSort() {
  std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(v1.begin(), v1.end(), g);
  std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  std::sort(v1.begin(), v1.end());
  std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  std::sort(v1.begin(), v1.end(), [](const int v1, const int v2) {return v1 > v2; });
  std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';



  std::vector<int> v2{};
  auto total = std::count_if(v1.begin(), v1.end(), [](const int v1) {return v1 % 2 == 1; });
  v2.resize(total);
  std::copy_if(v1.begin(), v1.end(), v2.begin(), [](const int v1) {return v1 % 2 == 1; });
  std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
}