#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day8.txt");
    std::cout << "Star 1: " << day8star1(inputs) << std::endl;
    std::cout << "Star 2: " << day8star2(inputs) << std::endl;
}
