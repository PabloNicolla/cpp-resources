#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string_view>
#include <string>
#include "mutexExample.h"

namespace {
  std::mutex mtx1;
  std::mutex mtx2;
  std::mutex mtx3;
}

void sharedAddOperation(int& toAdd1, int& toAdd2, int& toAdd3) {
  mtx1.lock();
  toAdd1 += 10;
  mtx1.unlock();
  mtx2.lock();
  toAdd2 += 20;
  mtx2.unlock();
  mtx3.lock();
  toAdd3 += 40;
  mtx3.unlock();
}

void sharedPrintOpearation(std::string_view sv) {
  mtx1.lock();
  std::cout << "Let's print it...\n";
  std::cout << "preparing...\n";
  std::cout << sv << "\n";
  std::cout << "done printing\n";
  mtx1.unlock();
}

void testMutex() {
  int x{}, y{}, z{};
  std::vector<std::thread> threads{};
  for (size_t i{}; i < 50; ++i) {
    threads.emplace_back(sharedAddOperation, std::ref(x), std::ref(y), std::ref(z));
  }
  for (auto& thread : threads) {
    thread.join();
  }
  std::cout << x << " " << y << " " << z << "\n\n";

  std::vector<std::string> toPrint{
    "string number 1",
    "string number 2",
    "string number 3",
    "string number 4",
    "string number 5",
    "string number 6",
    "string number 7",
    "string number 8",
    "string number 9",
    "string number 10",
  };
  threads.clear();
  for (const auto& str : toPrint) {
    threads.emplace_back(sharedPrintOpearation, str);
  }
  for (auto& thread : threads) {
    thread.join();
  }
}