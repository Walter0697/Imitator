#pragma once

#include "../defs.h"

class DropRate
{

public:

	DropRate();							//constructor
	~DropRate();						//destructor

	int multiplier;						//multiplier of the chances

	int tools_chance[NUM_OF_TOOLS];		//drop rate for toolSet

	int getToolChance(int);				//get the chance of the tool
	void unlock(int);					//unlock a tool from the game
};