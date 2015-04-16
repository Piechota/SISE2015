#include <utility>
#include "Stats.h"

Stats::Stats(std::string filename)
{
	file.open(filename);
}

Stats::~Stats()
{
	if (file.is_open())
	{
		file.flush();
		file.close();
	}
}

void Stats::AddPlayer(Player* player)
{
	if (stats.find(player) == stats.end())
	{
		PerPlayerStats* stat = new PerPlayerStats();
		stat->kills = 0;
		stat->deaths = 0;
		stat->survival = 0;
		stat->processingTimeSum = 0.0f;
		stat->turns = 0;

		stats.insert(std::make_pair(player, stat));
	}
}

void Stats::AddKill(Player* player)
{

}

void Stats::AddDeath(Player* player)
{

}

void Stats::AddSurvival(Player* player)
{

}

void Stats::AddProcessingTime(Player* player, float time)
{

}

void Stats::AddTurn(Player* player)
{

}
