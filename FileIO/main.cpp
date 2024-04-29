#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

struct Employee
{
    // ID,Name,Age,Occupation,Salary,Department,JoinDate
    std::string name;
    std::string occupation;
    std::string joinDate;
    std::string department;
    int ID;
    int age;
    int salary;
};

void readFile()
{
    std::ifstream file("data.txt");
    if (!file)
    {
        std::cerr << "Error opening file\n";
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        }
}

int main()
{
}