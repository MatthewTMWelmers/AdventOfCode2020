#pragma once

#include <boost/lexical_cast.hpp>
#include <fstream>
#include <regex>

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

template<class T>
int indexOf(std::vector<T> vec, T item) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == item) {
            return i;
        }
    }

    return -1;
}

template<class T>
int all(std::vector<T> vec,  std::function<int (T)> fn) {
    for (T t : vec) {
        if (!fn(t)) {
            return 0;
        }
    }

    return 1;
}

template<class T>
std::vector<T> split(std::string s, std::string regexStr) {
    std::vector<T> vals;
    std::regex regex(regexStr);
    std::smatch match;

    while (std::regex_search(s, match, regex)) {
        vals.push_back(boost::lexical_cast<T>(match.prefix()));
        s = match.suffix();
    }

    vals.push_back(boost::lexical_cast<T>(s));
    return vals;
}