#include <string>
#include <vector>
#include <iostream>

#include "advent.h"
#include "Util.h"

int main()
{
    //std::vector<int> inputs1 = linesFromFile<int>("Input/Day1.txt");
    //std::vector<std::string> inputs2 = linesFromFile<std::string>("Input/Day2.txt");
    //std::vector<std::string> inputs3 = linesFromFile<std::string>("Input/Day3.txt");
    //std::vector<std::string> inputs4 = linesFromFile<std::string>("Input/Day4.txt");
    //std::vector<std::string> inputs5 = linesFromFile<std::string>("Input/Day5.txt");
    //std::vector<std::string> inputs6 = linesFromFile<std::string>("Input/Day6.txt");
    //std::vector<std::string> inputs7 = linesFromFile<std::string>("Input/Day7.txt");
    //std::vector<std::string> inputs8 = linesFromFile<std::string>("Input/Day8.txt");
    //std::vector<long long> inputs9 = linesFromFile<long long>("Input/Day9.txt");
    //std::vector<int> inputs10 = linesFromFile<int>("Input/Day10.txt");
    //std::vector<std::string> inputs11 = linesFromFile<std::string>("Input/Day11.txt");
    //std::vector<std::string> inputs12 = linesFromFile<std::string>("Input/Day12.txt");
    //std::vector<std::string> inputs13 = linesFromFile<std::string>("Input/Day13.txt");
    //std::vector<std::string> inputs14 = linesFromFile<std::string>("Input/Day14.txt");
    //std::vector<int> inputs15 = day15inputs();
    //std::vector<std::string> inputs16 = linesFromFile<std::string>("Input/Day16.txt");
    //std::vector<std::string> inputs17 = linesFromFile<std::string>("Input/Day17.txt");
    //std::vector<std::string> inputs18 = linesFromFile<std::string>("Input/Day18.txt");
    //std::vector<std::string> inputs19 = linesFromFile<std::string>("Input/Day19.txt");
    //std::vector<std::string> inputs20 = linesFromFile<std::string>("Input/Day20.txt");
    //std::vector<std::string> inputs21 = linesFromFile<std::string>("Input/Day21.txt");
    std::vector<std::string> inputs22 = linesFromFile<std::string>("Input/Day22.txt");

    //std::cout << "Day 1 Star 1: " << day1star1(inputs1) << std::endl;
    //std::cout << "Day 1 Star 2: " << day1star2(inputs1) << std::endl;
    //std::cout << "Day 2 Star 1: " << day2star1(inputs2) << std::endl;
    //std::cout << "Day 2 Star 2: " << day2star2(inputs2) << std::endl;
    //std::cout << "Day 3 Star 1: " << day3star1(inputs3) << std::endl;
    //std::cout << "Day 3 Star 2: " << day3star2(inputs3) << std::endl;
    //std::cout << "Day 4 Star 1: " << day4star1(inputs4) << std::endl;
    //std::cout << "Day 4 Star 2: " << day4star2(inputs4) << std::endl;
    //std::cout << "Day 5 Star 1: " << day5star1(inputs5) << std::endl;
    //std::cout << "Day 5 Star 2: " << day5star2(inputs5) << std::endl;
    //std::cout << "Day 6 Star 1: " << day6star1(inputs6) << std::endl;
    //std::cout << "Day 6 Star 2: " << day6star2(inputs6) << std::endl;
    //std::cout << "Day 7 Star 1: " << day7star1(inputs7) << std::endl;
    //std::cout << "Day 7 Star 2: " << day7star2(inputs7) << std::endl;
    //std::cout << "Day 8 Star 1: " << day8star1(inputs8) << std::endl;
    //std::cout << "Day 8 Star 2: " << day8star2(inputs8) << std::endl;
    //std::cout << "Day 9 Star 1: " << day9star1(inputs9) << std::endl;
    //std::cout << "Day 9 Star 2: " << day9star2(inputs9) << std::endl;
    //std::cout << "Day 10 Star 1: " << day10star1(inputs10) << std::endl;
    //std::cout << "Day 10 Star 2: " << day10star2(inputs10) << std::endl;
    //std::cout << "Day 11 Star 1: " << day11star1(inputs11) << std::endl;
    //std::cout << "Day 11 Star 2: " << day11star2(inputs11) << std::endl;
    //std::cout << "Day 12 Star 1: " << day12star1(inputs12) << std::endl;
    //std::cout << "Day 12 Star 2: " << day12star2(inputs12) << std::endl;
    //std::cout << "Day 13 Star 1: " << day13star1(inputs13) << std::endl;
    //std::cout << "Day 13 Star 2: " << day13star2(inputs13) << std::endl;
    //std::cout << "Day 14 Star 1: " << day14star1(inputs14) << std::endl;
    //std::cout << "Day 14 Star 2: " << day14star2(inputs14) << std::endl;
    //std::cout << "Day 15 Star 1: " << day15star1(inputs15) << std::endl;
    //std::cout << "Day 15 Star 2: " << day15star2(inputs15) << std::endl;
    //std::cout << "Day 16 Star 1: " << day16star1(inputs16) << std::endl;
    //std::cout << "Day 16 Star 2: " << day16star2(inputs16) << std::endl;
    //std::cout << "Day 17 Star 1: " << day17star1(inputs17) << std::endl;
    //std::cout << "Day 17 Star 2: " << day17star2(inputs17) << std::endl;
    //std::cout << "Day 18 Star 1: " << day18star1(inputs18) << std::endl;
    //std::cout << "Day 18 Star 2: " << day18star2(inputs18) << std::endl;
    //std::cout << "Day 19 Star 1: " << day19star1(inputs19) << std::endl;
    //std::cout << "Day 19 Star 2: " << day19star2(inputs19) << std::endl;
    //std::cout << "Day 20 Star 1: " << day20star1(inputs20) << std::endl;
    //std::cout << "Day 20 Star 2: " << day20star2(inputs20) << std::endl;
    //std::cout << "Day 21 Star 1: " << day21star1(inputs21) << std::endl;
    //std::cout << "Day 21 Star 2: " << day21star2(inputs21) << std::endl;
    //std::cout << "Day 22 Star 1: " << day22star1(inputs22) << std::endl;
    //std::cout << "Day 22 Star 2: " << day22star2(inputs22) << std::endl;
    std::cout << "Day 23 Star 1: " << day23star1("872495136") << std::endl;
    std::cout << "Day 23 Star 2: " << day23star2("872495136") << std::endl;
}
