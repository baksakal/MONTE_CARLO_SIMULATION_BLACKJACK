#pragma once

enum class CardEnum {
	Card_Ace,
	Card_2,
	Card_3,
	Card_4,
	Card_5,
	Card_6,
	Card_7,
	Card_8,
	Card_9,
	Card_10,
	Card_Jack,
	Card_Queen,
	Card_King,
	INVALID_CARD
};

class SimulationInterface {
public:
	virtual void initializeSimulation(CardEnum firstCard, CardEnum secondCard, CardEnum dealerCard) = 0;
	virtual void runSim(int numberOfTrialsforEachTarget) = 0;
	virtual void getResults(const int &target, int& numberOfWins, int& numberOfLosses) const = 0;
	virtual void testHitRandomness(int trials) const = 0;
};
