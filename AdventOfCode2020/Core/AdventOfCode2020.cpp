#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day13.txt");
    std::cout << "Star 1: " << day13star1(inputs) << std::endl;
    std::cout << "Star 2: " << day13star2(inputs) << std::endl;
}
