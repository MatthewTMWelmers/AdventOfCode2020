#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day16.txt");
    std::cout << "Star 1: " << day16star1(inputs) << std::endl;
    std::cout << "Star 2: " << day16star2(inputs) << std::endl;
}
