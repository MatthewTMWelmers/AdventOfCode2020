#include <vector>
#include <string>
#include <deque>

#include "../Core/Util.h"

int war(std::deque<int>* player1, std::deque<int>* player2) {
	while (!player1->empty() && !player2->empty()) {
		int p1Card = player1->front();
		int p2Card = player2->front();

		player1->pop_front();
		player2->pop_front();

		if (p1Card > p2Card) {
			player1->push_back(p1Card);
			player1->push_back(p2Card);
		}
		else if (p2Card > p1Card) {
			player2->push_back(p2Card);
			player2->push_back(p1Card);
		}
	}

	return player1->empty() ? 0 : 1;
}

int score(std::deque<int> hand) {
	int sum = 0;
	for (size_t i = hand.size(); i > 0; i--) {
		sum += i * hand.front();
		hand.pop_front();
	}
	
	return sum;
}

int rWar(std::deque<int>* player1, std::deque<int>* player2) {
	std::vector<std::deque<int>>* prevHands1 = new std::vector<std::deque<int>>[player1->size() + player2->size()];
	std::vector<std::deque<int>>* prevHands2 = new std::vector<std::deque<int>>[player1->size() + player2->size()];
	for (size_t i = 0; i < player1->size() + player2->size(); i++) {
		prevHands1[i] = std::vector<std::deque<int>>();
		prevHands2[i] = std::vector<std::deque<int>>();
	}

	while (!player1->empty() && !player2->empty()) {
		std::vector<std::deque<int>> prevHand1 = prevHands1[player1->size()];
		std::vector<std::deque<int>> prevHand2 = prevHands2[player1->size()];

		for (size_t i = 0; i < prevHand1.size(); i++) {
			if (prevHand1[i].front() == player1->front() && prevHand2[i].front() == player2->front()) {
				if (prevHand1[i] == *player1) {
					if (prevHand2[i] == *player2) {
						delete[] prevHands1;
						delete[] prevHands2;
						return 1;
					}
				}
			}
		}

		prevHands1[player1->size()].push_back(std::deque<int>(*player1));
		prevHands2[player1->size()].push_back(std::deque<int>(*player2));

		int p1Card = player1->front();
		int p2Card = player2->front();

		player1->pop_front();
		player2->pop_front();

		int winner;
		if (player1->size() >= p1Card && player2->size() >= p2Card) {
			std::deque<int> copy1(*player1);
			std::deque<int> copy2(*player2);

			while (copy1.size() > p1Card) {
				copy1.pop_back();
			}

			while (copy2.size() > p2Card) {
				copy2.pop_back();
			}

			winner = rWar(&copy1, &copy2);
		}
		else {
			winner = p1Card > p2Card;
		}

		if (winner) {
			player1->push_back(p1Card);
			player1->push_back(p2Card);
		}
		else {
			player2->push_back(p2Card);
			player2->push_back(p1Card);
		}
	}

	delete[] prevHands1;
	delete[] prevHands2;
	return player1->empty() ? 0 : 1;
}


int day22star1(std::vector<std::string> inputs) {
	int idx = indexOf<std::string>(inputs, "");

	std::deque<int> player1;
	std::deque<int> player2;

	for (std::string card : std::vector<std::string>(inputs.begin() + 1, inputs.begin() + idx)) {
		player1.push_back(stoll(card));
	}
	for (std::string card : std::vector<std::string>(inputs.begin() + idx + 2, inputs.end())) {
		player2.push_back(stoll(card));
	}

	if (war(&player1, &player2)) {
		return score(player1);
	}
	else {
		return score(player2);
	}
}

int day22star2(std::vector<std::string> inputs) {
	int idx = indexOf<std::string>(inputs, "");

	std::deque<int> player1;
	std::deque<int> player2;

	for (std::string card : std::vector<std::string>(inputs.begin() + 1, inputs.begin() + idx)) {
		player1.push_back(stoll(card));
	}
	for (std::string card : std::vector<std::string>(inputs.begin() + idx + 2, inputs.end())) {
		player2.push_back(stoll(card));
	}

	if (rWar(&player1, &player2)) {
		return score(player1);
	}
	else {
		return score(player2);
	}
}