#include <string>
#include <vector>
#include "../Core/Util.h"
#include "../ClassHeaders/Ticket.h"

struct TicketInput {
	TicketInput(std::vector<std::string> inputs) {
		std::regex regex("^(.*): (\\d+)-(\\d+) or (\\d+)-(\\d+)$");
		std::smatch match;

		int mode = 0;
		for (std::string input : inputs) {
			if (input.empty() || mode == 1 || mode == 3) {
				mode++;
			}
			else if (mode == 0) {
				std::regex_match(input, match, regex);
				fields.push_back(TicketField(match.str(1), stoi(match.str(2)), stoi(match.str(3)), stoi(match.str(4)), stoi(match.str(5))));
			}
			else if (mode == 2) {
				yourTicket = Ticket(split<int>(input, ","));
			}
			else if (mode == 4) {
				nearbyTickets.push_back(Ticket(split<int>(input, ",")));
			}
		}
	}

	std::vector<TicketField> fields;
	std::vector<Ticket> nearbyTickets;
	Ticket yourTicket;
};

int day16star1(std::vector<std::string> inputs) {
	TicketInput in(inputs);

	int invalids = 0;
	for (Ticket t : in.nearbyTickets) {
		invalids += t.invalids(in.fields);
	}

	return invalids;
}

long long  day16star2(std::vector<std::string> inputs) {
	TicketInput in(inputs);

	std::vector<Ticket> ticketCpy(in.nearbyTickets);
	in.nearbyTickets.clear();
	std::copy_if(ticketCpy.begin(), ticketCpy.end(), std::back_inserter(in.nearbyTickets), [=](Ticket t) {return t.valid(in.fields); });

	std::vector<std::vector<TicketField>> possibleFields;
	for (size_t i = 0; i < in.fields.size(); i++) {
		possibleFields.push_back(std::vector<TicketField>(in.fields));
	}

	possibleFields = in.yourTicket.filterPossibleFields(possibleFields);

	for (Ticket t : in.nearbyTickets) {
		possibleFields = t.filterPossibleFields(possibleFields);
	}

	std::vector<std::vector<std::string>> possibleFieldNames;
	for (std::vector<TicketField> pf : possibleFields) {
		std::vector<std::string> names;
		for (TicketField f : pf) {
			names.push_back(f.name);
		}
		possibleFieldNames.push_back(names);
	}

	while (!all<std::vector<std::string>>(possibleFieldNames, [](auto s) -> int { return s.size() == 1; })) {
		for (size_t i = 0; i < possibleFieldNames.size(); i++) {
			if (possibleFieldNames[i].size() == 1) {
				for (size_t j = 0; j < possibleFieldNames.size(); j++) {
					if (i != j) {
						int idx = indexOf(possibleFieldNames[j], possibleFieldNames[i][0]);
						if (idx != -1) {
							possibleFieldNames[j].erase(possibleFieldNames[j].begin() + idx);
						}
					}
				}
			}
		}
	}

	long long prodVals = 1;
	for (size_t i = 0; i < possibleFieldNames.size(); i++) {
		if (possibleFieldNames[i][0].substr(0, 9) == "departure") {
			prodVals *= in.yourTicket[i];
		}
	}

	return prodVals;
}

