#include "run_tests.h"

#if RUN_TESTS == 1
#include <doctest/doctest.h>
#endif

#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "readFile_multithread.h"


void processLine(const std::string& line, Employee& emp) {
  std::istringstream iss{ line };
  std::string token{};

  std::getline(iss, token, ',');
  emp.ID = stoi(token);

  std::getline(iss, emp.name, ',');

  std::getline(iss, token, ',');
  emp.age = stoi(token);

  std::getline(iss, emp.occupation, ',');

  std::getline(iss, token, ',');
  emp.salary = stoi(token);

  std::getline(iss, emp.department, ',');
  std::getline(iss, emp.joinDate, ',');
}

void processFile() {
  std::ifstream file{ "data.txt" };
  if (!file) {
    std::cerr << "ERROR: data.txt could not be opened\n";
    return;
  }

  constexpr int threadNumber{ 5 };
  std::vector<Employee> employees{};
  std::vector<std::thread> threads{};
  std::string line{};

  employees.reserve(threadNumber);
  size_t empIndex{};

  std::getline(file, line);
  while (std::getline(file, line)) {
    threads.emplace_back(processLine, std::move(line), std::ref(employees.emplace_back()));
    ++empIndex;
    if (empIndex % threadNumber == 0) {
      for (size_t i{}; i < threads.size(); ++i) {
        threads[i].join();
      }
      employees.reserve(threadNumber + empIndex);
      threads.clear();
    }
  }
  for (size_t i{}; i < threads.size(); ++i) {
    threads[i].join();
  }
  for (const auto& emp : employees) {
    emp.print();
    std::cout << '\n';
  }
}

#if RUN_TESTS == 1

#endif
