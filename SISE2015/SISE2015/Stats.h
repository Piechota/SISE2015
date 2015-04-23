#ifndef _STATS_H_
#define _STATS_H_

#include "Headers.h"

class Stats
{
public:
	Stats(std::string filename);
	~Stats();

	void SaveToFile();

	void AddPlayer(Player* const player);
	void AddKill(Player* const player);
	void AddDeath(Player* const player);
	void AddSurvival(Player* const player);
	void AddProcessingTime(Player* const player, const float time);
	void AddTurn(Player* const player);

private:
	struct PerPlayerStats
	{
		uint32_t kills;
		uint32_t deaths;
		uint32_t survival;
		float processingTimeSum;
		uint32_t turns;
	};

	std::map<Player*, PerPlayerStats*> stats;
	std::ofstream file;
};

#endif