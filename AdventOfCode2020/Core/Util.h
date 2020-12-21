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
        if (match.prefix().length() > 0) {
            vals.push_back(boost::lexical_cast<T>(match.prefix()));
        }
        s = match.suffix();
    }

    if (s.length() > 0) {
        vals.push_back(boost::lexical_cast<T>(s));
    }
    return vals;
}

static void rotate(std::vector<std::string>* vec) {
    std::vector<std::string> rotVec;
    for (size_t i = 0; i < (*vec)[0].size(); i++) {
        rotVec.push_back("");
        for (size_t j = 0; j < vec->size(); j++) {
            rotVec[i] += (*vec)[vec->size() - j - 1][i];
        }
    }

    *vec = rotVec;
}

static void ccRotate(std::vector<std::string>* vec) {
    rotate(vec);
    rotate(vec);
    rotate(vec);
}

static int parseStringAsBinary(std::string s, char oneVal) {
    int binary = 0;
    for (char c : s) {
        binary <<= 1;
        binary += (c == oneVal) ? 1 : 0;
    }

    return binary;
}