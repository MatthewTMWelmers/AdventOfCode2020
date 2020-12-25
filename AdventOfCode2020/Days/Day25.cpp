#include <vector>

long long loop(long long subjectNum, long long startVal, size_t iter) {
	while (iter > 0) {
		startVal *= subjectNum;
		startVal %= 20201227;
		iter--;
	}

	return startVal;
}

long long day25() {
	long long loopSize = 1;
	long long loopVal = 1;
	while ((loopVal = loop(7, loopVal, 1)) != 10943862) {
		loopSize++;
	}

	loopVal = 1;
	return loop(12721030, loopVal, loopSize);
}