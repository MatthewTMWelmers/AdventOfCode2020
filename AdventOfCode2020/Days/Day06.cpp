#include <string>
#include <vector>
#include <set>
#include <regex>

std::vector<std::set<char>> unionQuestionairs(std::vector<std::string> inputs) {
	std::vector<std::set<char>> result;
	std::set<char>* s = new std::set<char>();

	for (std::string line : inputs) {
		if (line.empty()) {
			result.push_back(*s);
			s = new std::set<char>();
		}
		else {
			for (char c : line) {
				s->insert(c);
			}
			
		}
	}

	result.push_back(*s);
	return result;
}

std::vector<char> fullVector() {
	std::vector<char> v;
	for (char x = 'a'; x <= 'z'; x++) {
		v.push_back(x);
	}

	return v;
}

std::vector<char> intersection(std::vector<char>& v1, std::vector<char>& v2) {
	std::vector<char> v3;

	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}

std::vector<std::vector<char>> intersectionQuestionairs(std::vector<std::string> inputs) {
	std::vector<std::vector<char>> result;
	std::vector<char> v = fullVector();

	for (std::string line : inputs) {
		if (line.empty()) {
			result.push_back(v);
			v = fullVector();
		}
		else {
			std::vector<char> c = std::vector<char>(line.c_str(), line.c_str() + line.length());
			v = intersection(v, c);
		}
	}

	result.push_back(v);
	return result;
}



int day6star1(std::vector<std::string> inputs) {
	std::vector<std::set<char>> qs = unionQuestionairs(inputs);

	int yes = 0;
	for (std::set<char> q : qs) {
		yes += q.size();
	}

	return yes;
}
int day6star2(std::vector<std::string> inputs) {
	std::vector<std::vector<char>> qs = intersectionQuestionairs(inputs);

	int yes = 0;
	for (std::vector<char> q : qs) {
		yes += q.size();
	}

	return yes;
}