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

int numberOfRootsOfQuadraticEquation(double a, double b, double c)
{
	double delta = b * b - 4 * a * c;
	if (delta > 0) return 2;
	if (delta == 0) return 1;
	if (delta < 0) return 0;
}
