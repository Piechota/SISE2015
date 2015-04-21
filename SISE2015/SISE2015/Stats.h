#ifndef _STATS_H_
#define _STATS_H_

#include "Headers.h"

class Stats
{
public:
	Stats(std::string filename);
	~Stats();

	void SaveToFile();

	void AddPlayer(Player* player);
	void AddKill(Player* player);
	void AddDeath(Player* player);
	void AddSurvival(Player* player);
	void AddProcessingTime(Player* player, float time);
	void AddTurn(Player* player);

private:
	struct PerPlayerStats
	{
		int kills;
		int deaths;
		int survival;
		float processingTimeSum;
		int turns;
	};

	std::map<Player*, PerPlayerStats*> stats;
	std::ofstream file;
};

#endif