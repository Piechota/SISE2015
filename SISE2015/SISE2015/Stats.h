#ifndef _STATS_H_
#define _STATS_H_

#include "Headers.h"

class Stats
{
public:
	Stats(const std::string& filename);
	~Stats();

	void SaveToFile();

	void AddPlayer(const std::string& player);
	void AddKill(const std::string& player);
	void AddDeath(const std::string& player);
	void AddSurvival(const std::string& player);
	void AddProcessingTime(const std::string& player, const float time);
	void AddTurn(const std::string& player);

private:
	struct PerPlayerStats
	{
		uint32_t kills;
		uint32_t deaths;
		uint32_t survival;
		float processingTimeSum;
		uint32_t turns;
	};

	std::map<const std::string, PerPlayerStats*> stats;
	std::ofstream file;
};

#endif