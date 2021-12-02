#include "Location.h"

Location::Location()
	: Location(0, 0)
{
}

Location::Location(int x, int y)
	: x(x)
	, y(y)
{
}

bool Location::operator==(const Location & rhs) const
{
	return this->x == rhs.x && this->y == rhs.y;
}
