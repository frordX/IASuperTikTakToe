#pragma once
#include <utility>
#include "Enums.h"

class PlayerInput
{
	bool isAgainstMachine = false;
public:
	std::pair<int, int> GetPlayerInput(Colour player);
};


