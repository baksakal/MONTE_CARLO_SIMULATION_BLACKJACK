#include "Simulation.h"
#include <iostream>

CardEnum pickRandomCard(void);
int getCardValue(CardEnum card);
void addCardToScore(int cardValueToAdd, int& playerScoreThisGame, int& aceCounter);
void decideGameResult(int& playerScoreThisGame, int& dealerScoreThisGame, Simulation::Play_t& play);

Simulation::Simulation()
{
    // Default constructor
}
Simulation::~Simulation()
{
    // Destructor
}

void Simulation::initializeSimulation(CardEnum firstCard, CardEnum secondCard, CardEnum dealerCard)
{
    // Initialize the simulation.
    this->firstCard = firstCard;
    this->secondCard = secondCard;
    this->dealerCard = dealerCard;

}

void Simulation::runSim(int numberOfTrialsforEachTarget)
{
    for (int currentTarget = 12; currentTarget <= 21; currentTarget++)
    {
        Play_t play;
        play.losses = 0;
        play.wins = 0;
        for (int j = 0; j < numberOfTrialsforEachTarget; j++)
        {
            int playerScoreThisGame = 0;
            int dealerScoreThisGame = 0;
            int aceCounterPlayer = 0;
            int aceCounterDealer = 0;
            // Player 1st card
            addCardToScore(getCardValue(this->firstCard), playerScoreThisGame, aceCounterPlayer);
            // Player 2nd card
            addCardToScore(getCardValue(this->secondCard), playerScoreThisGame, aceCounterPlayer);
            // Player 3rd... card
            while (playerScoreThisGame < currentTarget)
            {
                addCardToScore(getCardValue(pickRandomCard()), playerScoreThisGame, aceCounterPlayer);
            }
            // Dealer 1st card
            addCardToScore(getCardValue(this->dealerCard), dealerScoreThisGame, aceCounterDealer);
            while (dealerScoreThisGame < 17)
            {
                addCardToScore(getCardValue(pickRandomCard()), dealerScoreThisGame, aceCounterDealer);
            }
            decideGameResult(playerScoreThisGame, dealerScoreThisGame, play);
        }
        this->plays[currentTarget - 12] = play;
    }
} 

void decideGameResult(int& playerScoreThisGame, int& dealerScoreThisGame, Simulation::Play_t& play)
{
    if (playerScoreThisGame > 21) 
    {
        play.losses += 1;
    }
    else if (dealerScoreThisGame > 21) 
    {
        play.wins += 1;
    }
    else
    {
        if (dealerScoreThisGame >= playerScoreThisGame)
        {
            play.losses += 1;
        }
        else 
        {
            play.wins += 1;
        }
    }
}





CardEnum pickRandomCard(void) 
{
    return static_cast<CardEnum>(rand() % 13);
}

//return the corresponding value associated with the card, with face cards being 10 and aces counting as 11 (ace degrade to 1 logic is handled using ace flags)
int getCardValue(CardEnum card) 
{
    if (static_cast<int>(card) + 1 >= 10)
    {
        return 10;
    }
    else if (static_cast<int>(card) + 1 == 1) 
    {
        return 11;
    }
    else
    {   //if the card is not 1 and it is also not a face card, return the card value ie card between 2 and 10 (including)
        return static_cast<int>(card) + 1;
    }        
}

// We add aces as 11 and handle ace downgrade to 1 using ace flags.(an ace is directly added into the ace flag at first)
// Ace flags represent the aces that are being counted as 11.
// After adding the aces, we evaluate if we have to reduce the ace counter (as aces become 1 if the score exceeds 21)
// Reducing the ace counter results in -10 change in score, as 11 is reduced to 1

void addCardToScore(int cardValueToAdd, int& playerScoreThisGame, int& aceCounter)
{
    playerScoreThisGame += cardValueToAdd;

    if (cardValueToAdd == 11)
    {
        aceCounter += 1;
    }
    if (playerScoreThisGame > 21)
    {
        if (aceCounter > 0) 
        {
            playerScoreThisGame -= 10;
            aceCounter -= 1;
        }
    }
}

void Simulation::getResults(const int &target, int& numberOfWins, int& numberOfLosses) const 
{
    numberOfWins = plays[target - 12].wins;
    numberOfLosses = plays[target - 12].losses;
} 

void Simulation::testHitRandomness(int trials) const 
{ 
    std::string cards[] = { "Aces", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s", "Jacks", "Queens", "Kings" };
    int arr[13] = { 0 };
    for (int i = 0; i < trials; i++)
    {
        arr[rand() % 13] += 1;
    }
    for (int i = 0; i < 13; i++) 
    {   
        std::cout << cards[i] << "\t:" << arr[i] << "\t- %" << (((double) arr[i] / (double)(trials))) << std::endl;
    }
}
