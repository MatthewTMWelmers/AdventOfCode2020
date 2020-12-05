#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day5.txt");
    std::cout << "Day 5 star 1: " << day5star1(inputs) << std::endl;
    std::cout << "Day 5 star 2: " << day5star2(inputs) << std::endl;
}
