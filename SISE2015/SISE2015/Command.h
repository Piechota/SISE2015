#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "Headers.h"

class Command
{
public:
	Command();
	~Command();

	virtual void Execute() = 0;
};

#endif