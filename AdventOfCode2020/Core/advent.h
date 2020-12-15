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

int day6star1(std::vector<std::string> inputs);
int day6star2(std::vector<std::string> inputs);

int day7star1(std::vector<std::string> inputs);
int day7star2(std::vector<std::string> inputs);

int day8star1(std::vector<std::string> inputs);
int day8star2(std::vector<std::string> inputs);

long long day9star1(std::vector<long long> inputs);
long long day9star2(std::vector<long long> inputs);

int day10star1(std::vector<int> inputs);
long long day10star2(std::vector<int> inputs);

int day11star1(std::vector<std::string> inputs);
int day11star2(std::vector<std::string> inputs);

int day12star1(std::vector<std::string> inputs);
int day12star2(std::vector<std::string> inputs);

long long day13star1(std::vector<std::string> inputs);
long long day13star2(std::vector<std::string> inputs);

long long day14star1(std::vector<std::string> inputs);
long long day14star2(std::vector<std::string> inputs);

int day15star1(std::vector<int> inputs);
int day15star2(std::vector<int> inputs);

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

std::vector<int> day15inputs() {
    std::vector<int> in;
    in.push_back(5);
    in.push_back(1);
    in.push_back(9);
    in.push_back(18);
    in.push_back(13);
    in.push_back(8);
    in.push_back(0);

    return in;
}