#pragma once

#include "../defs.h"

class DropRate
{

public:

	DropRate();
	~DropRate();

	int multiplier;

	//drop rate for toolSet
	int tools_chance[NUM_OF_TOOLS];

	int getToolChance(int);
	void unlock(int);
};