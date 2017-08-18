#pragma once

#include "../defs.h"

class DropRate
{

public:

	DropRate();
	~DropRate();

	int multiplier;

	//drop rate for toolSet
	int tools_chance[5];

	int getToolChance(int);
	void unlock(int);
};