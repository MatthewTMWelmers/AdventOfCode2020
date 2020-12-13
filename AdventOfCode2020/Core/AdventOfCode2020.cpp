#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day6.txt");
    std::cout << "Day 6 star 1: " << day6star1(inputs) << std::endl;
    std::cout << "Day 6 star 2: " << day6star2(inputs) << std::endl;
}
