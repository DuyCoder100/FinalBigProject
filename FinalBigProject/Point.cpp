#include "stdafx.h"
#include "Point.h"


Point::Point()
{
	this->x = this->y = 0;
}


Point::~Point()
{
}

int Point::getPosRectBetwTwoPoint(const Point& A)
{
	if (A.x > this->x && A.y < this->y) return 1;
	if (A.x > this->x && A.y > this->y) return 2;
	if (A.x < this->x && A.y > this->y) return 3;
	return 4;
}
