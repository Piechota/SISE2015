#include <iostream>
#include <ctime>
#include "ExamplePlayer.h"

ExamplePlayer::ExamplePlayer(std::string name) : Player(name)
{

}

ExamplePlayer::ExamplePlayer(const ExamplePlayer& other) : Player(other)
{
	
}

DecisionInfo ExamplePlayer::ProcessAI(GraphInfo grapthInfo)
{
	return (Decision) ( (rand() % 10 + time(NULL) % 25 + grapthInfo ) % (int)(Decision::DECISION_COUNT) );
}