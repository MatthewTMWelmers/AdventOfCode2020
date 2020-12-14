#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day11.txt");
    std::cout << "Star 1: " << day11star1(inputs) << std::endl;
    std::cout << "Star 2: " << day11star2(inputs) << std::endl;
}
