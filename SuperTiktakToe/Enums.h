#pragma once
#include <map>

enum Colour
{
	X,
	O,
	Blank,
};

const char ColourToString[3] = {
'X',
'0',
' ',
};

const std::map<char, Colour> StringToColour = {
   {'X', Colour::X},
   {'0', Colour::O},
   {' ', Colour::Blank}
};