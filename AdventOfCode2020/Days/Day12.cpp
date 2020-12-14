#include <vector>
#include <string> 


int day12star1(std::vector<std::string> inputs) {
	std::vector<std::pair<char, char>> rots;
	rots.push_back(std::pair<char, char>('N', 'E'));
	rots.push_back(std::pair<char, char>('E', 'S'));
	rots.push_back(std::pair<char, char>('S', 'W'));
	rots.push_back(std::pair<char, char>('W', 'N'));

	char dir = 'E';
	int x = 0;
	int y = 0;

	for(std::string input : inputs) {
		char inst = input[0];
		if (inst == 'F') {
			inst = dir;
		}

		int magnitude = stoi(input.erase(0, 1));

		switch (inst) {
		case 'N': y += magnitude; break;
		case 'S': y -= magnitude; break;
		case 'E': x += magnitude; break;
		case 'W': x -= magnitude; break;

		case 'R':
			while (magnitude > 0) {
				for (std::pair<char, char> rot : rots) {
					if (rot.first == dir) {
						dir = rot.second;
						magnitude -= 90;
						break;
					}
				}
			}
			break;

		case 'L':
			while (magnitude > 0) {
				for (std::pair<char, char> rot : rots) {
					if (rot.second == dir) {
						dir = rot.first;
						magnitude -= 90;
						break;
					}
				}
			}
			break;
		}
	}

	return abs(x) + abs(y);
}

int day12star2(std::vector<std::string> inputs) {
	int sx = 0;
	int sy = 0;
	int wx = 10;
	int wy = 1;

	for (std::string input : inputs) {
		char inst = input[0];
		int magnitude = stoi(input.erase(0, 1));

		switch (inst) {
		case 'N': wy += magnitude; break;
		case 'S': wy -= magnitude; break;
		case 'E': wx += magnitude; break;
		case 'W': wx -= magnitude; break;
		case 'F': sx += magnitude * wx; sy += magnitude * wy; break;
		case 'R':
			while (magnitude > 0) {
				wx = -wx;
				wx ^= wy;
				wy ^= wx;
				wx ^= wy;
				magnitude -= 90;
			}
			break;

		case 'L':
			while (magnitude > 0) {
				wx ^= wy;
				wy ^= wx;
				wx ^= wy;
				wx = -wx;
				magnitude -= 90;
			}
			break;
		}
	}

	return abs(sx) + abs(sy);
}