#include "Headers.h"

Stats::Stats(const std::string& filename)
{
	file.open(filename, std::ofstream::app);
}

Stats::~Stats()
{
	for (auto& kv : stats)
	{
		delete kv.second;
	}

	file.close();
}

void Stats::SaveToFile()
{
	if (file.is_open())
	{
		file << "Statistics\n";

		file << "Stat/Player";
		for (auto& kv : stats)
		{
			file << ";";
			file << kv.first;
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

		/*file << "Processing time sum";
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
		file << "\n";*/

		file.flush();
	}
}

void Stats::AddPlayer(const std::string& player)
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

void Stats::AddKill(const std::string& player)
{
	stats[player]->kills++;
}

void Stats::AddDeath(const std::string& player)
{
	stats[player]->deaths++;
}

void Stats::AddSurvival(const std::string& player)
{
	stats[player]->survival++;
}

void Stats::AddProcessingTime(const std::string& player, const float time)
{
	stats[player]->processingTimeSum += time;
}

void Stats::AddTurn(const std::string& player)
{
	stats[player]->turns++;
}
