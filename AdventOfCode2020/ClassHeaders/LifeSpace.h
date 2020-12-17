#pragma once

class LifeSpace {
public:
	virtual int activeCount() = NULL;
	virtual void evolve() = NULL;
};

class LifeCube : public LifeSpace {
public:
	LifeCube(std::vector<std::string> init);
	int activeCount();
	void evolve();
private:
	int maxx, maxy, maxz;
	int*** active;
	int activeAround(int x, int y, int z);
	void persist(std::vector<std::tuple<int, int, int>> state);
	void clearActive();
	void alloc();
};

class LifeCube4 : public LifeSpace {
public:
	LifeCube4(std::vector<std::string> init);
	virtual int activeCount();
	virtual void evolve();
private:
	int maxx, maxy, maxz, maxw;
	int**** active;
	int activeAround(int x, int y, int z, int w);
	void persist(std::vector<std::tuple<int, int, int, int>> state);
	void clearActive();
	void alloc();
};