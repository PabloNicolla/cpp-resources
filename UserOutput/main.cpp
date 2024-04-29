#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void displayMenu(std::vector<std::string> menuItems)
{
    std::cout << "Menu:\n";
    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        std::cout << std::setw(3) << i + 1 << " - " << menuItems[i] << '\n';
    }
    std::cout << "Enter your choice [1.." + std::to_string(menuItems.size()) + "]: ";
}

void displayIDs(std::vector<std::string> IDs)
{
    std::cout << "Users IDs:\n";
    for (size_t i = 0; i < IDs.size(); ++i)
    {
        std::cout << std::setw(8) << std::setfill('0') << IDs[i] << " - "
                  << "some other info" << '\n';
    }
}

void formatCurrency(double amount)
{
    std::cout << std::fixed << std::setprecision(2) << "$" << amount;
}

int main()
{
    std::vector<std::string> menuItems{"Add", "Subtract", "Multiply", "Divide", "Quit"};
    displayMenu(menuItems);

    std::cout << "\n\n\n";

    std::vector<std::string> IDs{"1", "32", "1244", "4322", "2432432"};
    displayIDs(IDs);

    return 0;
}