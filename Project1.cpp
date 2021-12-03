// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <string>
#include "SimulationInterface.h"
#include "Simulation.h"

CardEnum getCardEnum(std::string in)
{
	std::transform(in.begin(), in.end(), in.begin(), ::toupper);
	if (in == "A" || in == "ACE")
		return CardEnum::Card_Ace;
	else if (in == "2")
		return CardEnum::Card_2;
	else if (in == "3")
		return CardEnum::Card_3;
	else if (in == "4")
		return CardEnum::Card_4;
	else if (in == "5")
		return CardEnum::Card_5;
	else if (in == "6")
		return CardEnum::Card_6;
	else if (in == "7")
		return CardEnum::Card_7;
	else if (in == "8")
		return CardEnum::Card_8;
	else if (in == "9")
		return CardEnum::Card_9;
	else if (in == "10")
		return CardEnum::Card_10;
	else if (in == "J" || in == "JACK")
		return CardEnum::Card_Jack;
	else if (in == "Q" || in == "QUEEN")
		return CardEnum::Card_Queen;
	else if (in == "K" || in == "KING")
		return CardEnum::Card_King;
	else
		return CardEnum::INVALID_CARD;
}

CardEnum readCard(std::string message)
{
	CardEnum retValue = CardEnum::INVALID_CARD;
	do {
		std::cout << message;
		std::string in;
		std::cin >> in; std::cin.ignore();
		retValue = getCardEnum(in);
	} while (retValue == CardEnum::INVALID_CARD);
	return retValue;
}

int readNumOfTrials(std::string message)
{
	int trials = 0;
	do {
		std::cout << message;
		std::string in;
		std::cin >> in; std::cin.ignore();
		try {
			trials = stoi(in);
		}
		catch (...) {
			std::cout << "Error: " << in << " is not a number!!\n";
			trials = 0;
		}
	} while (trials <= 0);
	return trials;
}

int main()
{
	printf("When asked please enter a card as A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K\n");
	CardEnum dealer = readCard("Please Enter The Dealers Open Card : ");
	CardEnum firstCard = readCard("Please Enter Your First Card : ");
	CardEnum secondCard = readCard("Please Enter Your Second Card : ");
	int trials = readNumOfTrials("Please Enter Number Of Trials : ");

	SimulationInterface* sim = new Simulation();
	sim->testHitRandomness(100000);

	sim->initializeSimulation(firstCard, secondCard, dealer);
	sim->runSim(trials);
	for (int i = 12; i <= 21; i++)
	{
		int wins, losses;
		sim->getResults(i, wins, losses);
		float probability = 0.0f;
		if (wins > 0 || losses > 0)
		{
			probability = ((float)wins) / (wins + losses);
		}
		std::cout << "Target:" << i << " - wins:" << wins << " - losses:" << losses << " - probability of win:" << probability << std::endl;
	}

	delete sim;
	system("Pause");
}

