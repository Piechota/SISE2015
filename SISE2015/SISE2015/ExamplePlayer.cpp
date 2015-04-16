#include <iostream>
#include <ctime>
#include "ExamplePlayer.h"

ExamplePlayer::ExamplePlayer() : Player()
{

}

ExamplePlayer::ExamplePlayer(const ExamplePlayer &other) : Player(other)
{
	
}

DecisionInfo ExamplePlayer::ProcessAI(GraphInfo grapthInfo)
{
	//here goes logic of AI, ease of use as a priority
	return (Decision) ( (rand() % 10 + time(NULL) % 25 + grapthInfo ) % (int)(Decision::DECISION_COUNT) );
}