#include <string>
#include <vector>
#include <regex>
#include <iostream>

std::vector<int> splitAndParse(std::string input) {
	std::vector<int> ints;
	std::regex regex("\\d+");
	std::smatch match;

	while (std::regex_search(input, match, regex)) {
		ints.push_back(stoi(match.str(0)));
		input = match.suffix();
	}

	return ints;
}

class Field {
public:
	Field(std::string name, int min1, int max1, int min2, int max2) {
		this->name = name;
		this->min1 = min1;
		this->max1 = max1;
		this->min2 = min2;
		this->max2 = max2;
	}

	int isValid(int val) {
		return (val >= min1 && val <= max1) || (val >= min2 && val <= max2);
	}
	
	std::string name;
	int min1;
	int max1;
	int min2;
	int max2;
};

class Ticket {
public:
	Ticket() { }

	Ticket(std::vector<int> fields) {
		this->fields = fields;
	}

	int invalids(std::vector<Field> fieldList) {
		int valid = 1;
		int invalid = 0;

		for (int i : fields) {
			valid = 0;
			for (Field f : fieldList) {
				valid += f.isValid(i);
			}
			if (!valid) {
				invalid += i;
			}
		}

		return invalid;
	}

	int valid(std::vector<Field> fieldList) {
		int valid;
		for (int i : fields) {
			valid = 0;
			for (Field f : fieldList) {
				valid += f.isValid(i);
			}
			if (!valid) {
				return 0;
			}
		}

		return 1;
	}

	int operator[](int f) const {
		return fields[f];
	}

private:
	std::vector<int> fields;
};

class Input {
public:
	Input(std::vector<std::string> inputs) {
		std::regex regex("^(.*): (\\d+)-(\\d+) or (\\d+)-(\\d+)$");
		std::smatch match;

		int mode = 0;
		for (std::string input : inputs) {
			if (input.empty() || mode == 1 || mode == 3) {
				mode++;
			}
			else if (mode == 0) {
				std::regex_match(input, match, regex);
				fields.push_back(Field(match.str(1), stoi(match.str(2)), stoi(match.str(3)), stoi(match.str(4)), stoi(match.str(5))));
			}
			else if (mode == 2) {
				yourTicket = Ticket(splitAndParse(input));
			}
			else if (mode == 4) {
				nearbyTickets.push_back(Ticket(splitAndParse(input)));
			}
		}
	}

	std::vector<Field> fields;
	std::vector<Ticket> nearbyTickets;
	Ticket yourTicket;
};

std::vector<std::vector<Field>> filter(std::vector<std::vector<Field>> initial, Ticket t) {
	for (int i = 0; i < initial.size(); i++) {
		std::vector<Field> possible(initial[i]);
		initial[i].clear();
		std::copy_if(possible.begin(), possible.end(), std::back_inserter(initial[i]), [=](Field f) {return f.isValid(t[i]); });
	}

	return initial;
}

int index(std::vector<std::string> v, std::string s) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == s) {
			return i;
		}
	}

	return -1;
}

int allUnique(std::vector<std::vector<std::string>> set) {
	for (std::vector<std::string> s : set) {
		if (s.size() > 1) {
			return 0;
		}
	}

	return 1;
}

int day16star1(std::vector<std::string> inputs) {
	Input in(inputs);

	int invalids = 0;
	for (Ticket t : in.nearbyTickets) {
		invalids += t.invalids(in.fields);
	}

	return invalids;
}

long long  day16star2(std::vector<std::string> inputs) {
	Input in(inputs);

	std::vector<Ticket> ticketCpy(in.nearbyTickets);
	in.nearbyTickets.clear();
	std::copy_if(ticketCpy.begin(), ticketCpy.end(), std::back_inserter(in.nearbyTickets), [=](Ticket t) {return t.valid(in.fields); });

	std::vector<std::vector<Field>> possibleFields;
	for (int i = 0; i < in.fields.size(); i++) {
		possibleFields.push_back(std::vector<Field>(in.fields));
	}

	possibleFields = filter(possibleFields, in.yourTicket);

	for (Ticket t : in.nearbyTickets) {
		possibleFields = filter(possibleFields, t);
	}

	std::vector<std::vector<std::string>> possibleFieldNames;
	for (std::vector<Field> pf : possibleFields) {
		std::vector<std::string> names;
		for (Field f : pf) {
			names.push_back(f.name);
		}
		possibleFieldNames.push_back(names);
	}

	while (!allUnique(possibleFieldNames)) {
		for (int i = 0; i < possibleFieldNames.size(); i++) {
			if (possibleFieldNames[i].size() == 1) {
				for (int j = 0; j < possibleFieldNames.size(); j++) {
					if (i != j) {
						int idx = index(possibleFieldNames[j], possibleFieldNames[i][0]);
						if (idx != -1) {
							possibleFieldNames[j].erase(possibleFieldNames[j].begin() + idx);
						}
					}
				}
			}
		}
	}

	long long prodVals = 1;
	for (int i = 0; i < possibleFieldNames.size(); i++) {
		if (possibleFieldNames[i][0].substr(0, 9) == "departure") {
			prodVals *= in.yourTicket[i];
		}
	}

	return prodVals;
}

