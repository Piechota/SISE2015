#ifndef _STATS_H_
#define _STATS_H_

#include "Headers.h"

class Stats
{
public:
	Stats(std::string filename);
	~Stats();

	void SaveToFile();

	void AddPlayer(const Player* const player);
	void AddKill(const Player* const player);
	void AddDeath(const Player* const player);
	void AddSurvival(const Player* const player);
	void AddProcessingTime(const Player* const player, const float time);
	void AddTurn(const Player* const player);

private:
	struct PerPlayerStats
	{
		uint32_t kills;
		uint32_t deaths;
		uint32_t survival;
		float processingTimeSum;
		uint32_t turns;
	};

	std::map<const Player*, PerPlayerStats*> stats;
	std::ofstream file;
};

#endif