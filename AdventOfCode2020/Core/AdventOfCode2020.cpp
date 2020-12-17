#include <string>
#include <vector>

#include "advent.h"

int main()
{
    std::vector<std::string> inputs = linesFromFile<std::string>("Input/Day17.txt");
    std::cout << "Star 1: " << day17star1(inputs) << std::endl;
    std::cout << "Star 2: " << day17star2(inputs) << std::endl;
}
