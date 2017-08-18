#include "dropRate.hpp"

DropRate::DropRate() 
{
	for (int i = 0; i < 5; i++) 
	{
		tools_chance[i] = 0;
	}
	multiplier = 1;
}

DropRate::~DropRate() {} 

int DropRate::getToolChance(int type)
{
	return tools_chance[type-1] * multiplier;
}

void DropRate::unlock(int type)
{
	tools_chance[type-1] = 30;
}