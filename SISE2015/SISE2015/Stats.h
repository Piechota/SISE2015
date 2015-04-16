#ifndef _STATS_H_
#define _STATS_H_

#include <fstream>
#include <map>
#include <string>
#include "Player.h"

class Stats
{
public:
	Stats(std::string filename);
	~Stats();

private:
	struct PerPlayerStats
	{
		int kills;
		int deaths;
		int survival;
		float processingTimeSum;
		float processingTimeAvg;
		int turns;
	};

	std::map<Player*, PerPlayerStats*> stats;
	std::ofstream file;
};

#endif