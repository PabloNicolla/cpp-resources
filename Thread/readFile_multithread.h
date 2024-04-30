#pragma once
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

void processLine(const std::string& line, Employee& emp);
void processFile();

