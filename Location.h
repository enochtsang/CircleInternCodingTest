#pragma once

class Location
{
public:
	Location();
	Location(int x, int y);

	bool operator==(const Location & rhs) const;

	int x = 0;
	int y = 0;
};

