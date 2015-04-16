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