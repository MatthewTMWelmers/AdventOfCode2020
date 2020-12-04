#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Day3.txt");
    std::cout << "Day 3 star 1: " << day3star1(inputs) << std::endl;
    std::cout << "Day 3 star 2: " << day3star2(inputs) << std::endl;
}
