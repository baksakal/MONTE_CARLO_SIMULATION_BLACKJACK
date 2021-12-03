#include "SimulationInterface.h"

class Simulation : public SimulationInterface 
{
    public:
        Simulation();
        ~Simulation();
        void initializeSimulation(CardEnum firstCard, CardEnum secondCard, CardEnum dealerCard);
        void runSim(int numberOfTrialsforEachTarget);
        void getResults(const int &target, int& numberOfWins, int& numberOfLosses) const;
        void testHitRandomness(int trials) const;
        typedef struct Play { //play struct holds the win and loss counts for each target score from 12 to 21
            int wins;
            int losses;
        }Play_t;
    private:
        Play_t plays[10];
        CardEnum firstCard;
        CardEnum secondCard;
        CardEnum dealerCard;

};