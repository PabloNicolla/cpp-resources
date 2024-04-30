#include <numeric>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "search&find.h"

void searchAndFind() {
  std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  auto ret1 = std::find(v1.begin(), v1.end(), 2);
  if (ret1 != v1.end()) {
    std::cout << "found!\n\n";
  }
  else {
    std::cout << "not found!\n\n";
  }

  auto ret2 = std::find(v1.begin(), v1.end(), 22);
  if (ret2 != v1.end()) {
    std::cout << "found!\n\n";
  }
  else {
    std::cout << "not found!\n\n";
  }

  std::string str{ "This is some random string that does not have any use tbh." };

  std::string search1{ "random" };
  auto ret3 = std::search(str.begin(), str.end(), search1.begin(), search1.end());
  if (ret3 != str.end()) {
    std::cout << "found!\n\n";
  }
  else {
    std::cout << "not found!\n\n";
  }

  std::string search2{ "not in" };
  auto ret4 = std::search(str.begin(), str.end(), search2.begin(), search2.end());
  if (ret4 != str.end()) {
    std::cout << "found!\n\n";
  }
  else {
    std::cout << "not found!\n\n";
  }
}