#include "Output.h"

int main()
{
  std::vector<std::string> menuItems{ "Add", "Subtract", "Multiply", "Divide", "Quit" };
  displayMenu(menuItems);

  std::cout << "\n\n";
  outputSplit('-');
  std::cout << "\n\n";

  std::vector<std::string> IDs{ "1", "32", "1244", "4322", "2432432" };
  displayIDs(IDs);

  return 0;
}