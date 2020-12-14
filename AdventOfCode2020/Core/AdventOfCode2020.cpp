#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day12.txt");
    std::cout << "Star 1: " << day12star1(inputs) << std::endl;
    std::cout << "Star 2: " << day12star2(inputs) << std::endl;
}
