#include <vector>
#include <algorithm>
#include <iterator>

#include "../ClassHeaders/Ticket.h"

int Ticket::invalids(std::vector<TicketField> fieldList) {
	int valid = 1;
	int invalid = 0;

	for (int i : fields) {
		valid = 0;
		for (TicketField f : fieldList) {
			valid += f.isValid(i);
		}
		if (!valid) {
			invalid += i;
		}
	}

	return invalid;
}

int Ticket::valid(std::vector<TicketField> fieldList) {
	int valid;
	for (int i : fields) {
		valid = 0;
		for (TicketField f : fieldList) {
			valid += f.isValid(i);
		}
		if (!valid) {
			return 0;
		}
	}

	return 1;
}


std::vector<std::vector<TicketField>> Ticket::filterPossibleFields(std::vector<std::vector<TicketField>> initial) {
	for (size_t i = 0; i < initial.size(); i++) {
		std::vector<TicketField> possible(initial[i]);
		initial[i].clear();
		std::copy_if(possible.begin(), possible.end(), std::back_inserter(initial[i]), [=](TicketField f) {return f.isValid((*this)[i]); });
	}

	return initial;
}