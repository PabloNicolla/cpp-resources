#include "run_tests.h"

#if RUN_TESTS == 1
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#endif

#if RUN_TESTS != 1

#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

struct Employee
{
  // ID,Name,Age,Occupation,Salary,Department,JoinDate
  std::string name{};
  std::string occupation{};
  std::string joinDate{};
  std::string department{};
  int ID{};
  int age{};
  int salary{};

  void print() const {
    std::cout << ID << ", " << name << ", " << age << ", " << occupation << ", " << salary << ", " << department << ", " << joinDate;
  }
};

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

  emp.joinDate = iss.str();
}

void processFile() {
  std::ifstream file{ "data.txt" };
  if (!file) {
    std::cerr << "ERROR: data.txt could not be opened\n";
    return;
  }

  std::vector<Employee> employees{};
  std::vector<std::thread> threads{};
  std::string line{};
  while (std::getline(file, line)) {
    threads.emplace_back(processLine, std::move(line), std::ref(employees.emplace_back()));
  }
  for (size_t i{}; i < threads.size(); ++i) {
    threads[i].join();
  }
  for (const auto& emp : employees) {
    emp.print();
    std::cout << '\n';
  }
}

int main()
{
    return 0;
}

#endif
