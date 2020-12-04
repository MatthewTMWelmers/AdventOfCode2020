#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day4.txt");
    std::cout << "Day 4 star 1: " << day4star1(inputs) << std::endl;
    std::cout << "Day 4 star 2: " << day4star2(inputs) << std::endl;
}
