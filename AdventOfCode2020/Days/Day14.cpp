#include <vector>
#include <string>
#include <regex>
#include <map>

void updateMask(std::string mask, long long* andMask, long long* orMask) {
	*andMask = ~0LL;
	*orMask = 0LL;

	for (char c : mask) {
		*andMask <<= 1;
		*andMask |= 1LL;

		*orMask <<= 1;

		if (c == '1') {
			*orMask |= 1LL;
		}

		if (c == '0') {
			*andMask &= ~1LL;
		}
	}
}

std::vector<long long> applyFloatingMask(std::string mask, long long addr) {
	std::vector<long long> addrs;
	addrs.push_back(addr);

	for (int i = 0; i < mask.size(); i++) {
		if (mask[mask.size() - i - 1] == 'X') {
			std::vector<long long> addrsCpy(addrs);
			addrs.clear();

			for (long long val : addrsCpy) {
				addrs.push_back(val);
				addrs.push_back(val ^ (1LL << i));
			}
		}
	}

	return addrs;
}

long long day14star1(std::vector<std::string> inputs) {
	std::map<long long, long long> mem;
	long long andMask;
	long long orMask;


	std::regex memRegex("mem\\[(\\d+)\\] = (\\d+)");
	std::smatch match;

	for (std::string cmd : inputs) {
		if (std::regex_match(cmd, std::regex("mask = [X01]{36}"))) {
			updateMask(cmd.erase(0, 7), &andMask, &orMask);
		}
		else {
			std::regex_match(cmd, match, memRegex);
			long long val = stoll(match.str(2));
			val &= andMask;
			val |= orMask;
			mem[stoi(match.str(1))] = val;
		}
	}

	long long sum = 0;
	for (const std::pair<long long, long long>& kv : mem) {
		sum += kv.second;
	}
	return sum;
}

long long day14star2(std::vector<std::string> inputs) {
	std::map<long long, long long> mem;
	std::string mask;
	long long andMask;
	long long orMask;

	std::regex memRegex("mem\\[(\\d+)\\] = (\\d+)");
	std::smatch match;

	for (std::string cmd : inputs) {
		if (std::regex_match(cmd, std::regex("mask = [X01]{36}"))) {
			mask = cmd.erase(0, 7);
			updateMask(mask, &andMask, &orMask);
		}
		else {
			std::regex_match(cmd, match, memRegex);
			long long val = stoll(match.str(2));
			for (long long addr : applyFloatingMask(mask, stoll(match.str(1)) | orMask)) {
				mem[addr] = val;
			}
		}
	}

	long long sum = 0;
	for (const std::pair<long long, long long>& kv : mem) {
		sum += kv.second;
	}
	return sum;
}