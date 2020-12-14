#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day14.txt");
    std::cout << "Star 1: " << day14star1(inputs) << std::endl;
    std::cout << "Star 2: " << day14star2(inputs) << std::endl;
}
