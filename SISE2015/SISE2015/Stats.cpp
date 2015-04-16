#include <utility>
#include "Stats.h"
#include "Player.h"

Stats::Stats(std::string filename)
{
	file.open(filename);
}

Stats::~Stats()
{
	if (file.is_open())
	{
		file << "Statistics\n";

		file << "Stat/Player";
		for (auto& kv : stats)
		{
			file << ";";
			file << kv.first->GetName();
		}
		file << "\n";

		file << "Kills";
		for (auto& kv : stats)
		{
			file << ";";
			file << kv.second->kills;
		}
		file << "\n";

		file << "Deaths";
		for (auto& kv : stats)
		{
			file << ";";
			file << kv.second->deaths;
		}
		file << "\n";

		file << "Survival";
		for (auto& kv : stats)
		{
			file << ";";
			file << kv.second->survival;
		}
		file << "\n";

		file << "Processing time sum";
		for (auto& kv : stats)
		{
			file << ";";
			file << kv.second->processingTimeSum;
		}
		file << "\n";

		file << "Processing time avg";
		for (auto& kv : stats)
		{
			file << ";";
			file << (kv.second->processingTimeSum / (float)kv.second->turns);
		}
		file << "\n";

		file << "Turns";
		for (auto& kv : stats)
		{
			file << ";";
			file << kv.second->turns;
		}
		file << "\n";

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
	stats[player]->kills++;
}

void Stats::AddDeath(Player* player)
{
	stats[player]->deaths++;
}

void Stats::AddSurvival(Player* player)
{
	stats[player]->survival++;
}

void Stats::AddProcessingTime(Player* player, float time)
{
	stats[player]->processingTimeSum += time;
}

void Stats::AddTurn(Player* player)
{
	stats[player]->turns++;
}
