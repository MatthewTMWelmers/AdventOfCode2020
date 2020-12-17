#pragma once
#include <string>

struct TicketField {
	TicketField(std::string name, int min1, int max1, int min2, int max2) {
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

	Ticket(std::vector<int> fields) { this->fields = fields; }
	int operator[](int f) const { return fields[f]; }
	int invalids(std::vector<TicketField> fieldList);
	int valid(std::vector<TicketField> fieldList);
	std::vector<std::vector<TicketField>> filterPossibleFields(std::vector<std::vector<TicketField>> initial);

	

private:
	std::vector<int> fields;
};