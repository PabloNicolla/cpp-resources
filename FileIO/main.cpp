#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

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