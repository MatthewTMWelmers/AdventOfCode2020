#pragma once

#include <boost/lexical_cast.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int day1star1(std::vector<int> inputs);
int day1star2(std::vector<int> inputs);

int day2star1(std::vector<std::string> inputs);
int day2star2(std::vector<std::string> inputs);

int day3star1(std::vector<std::string> inputs);
long long day3star2(std::vector<std::string> inputs);

int day4star1(std::vector<std::string> inputs);
int day4star2(std::vector<std::string> inputs);

int day5star1(std::vector<std::string> inputs);
int day5star2(std::vector<std::string> inputs);

template<class T>
std::vector<T> linesFromFile(std::string fileName) {
    std::string line;
    std::ifstream inputFile(fileName);
    std::vector<T> inputs;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            inputs.push_back(boost::lexical_cast<T>(line));
        }

        inputFile.close();
    }

    return inputs;
}