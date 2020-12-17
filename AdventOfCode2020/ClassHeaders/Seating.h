#pragma once
class Seating {
public:
	Seating(std::vector<std::string> inputs, int tolerance, int observeFloor);

	int isStable();
	void evolve();
	int occupied();

private:
	std::vector<std::string> board;
	int width;
	int height;
	int changed;
	int observeFloor;
	int tolerance;

	char nextChar(char curr, int surround);
	int surroundFilled(int x, int y);
	int directionFilled(int x, int y, int dx, int dy);
};