#pragma once
#include "Shape.h"

class CEllipse : public Shape
{
public:
	// Constructor, Destructor
	CEllipse();
	~CEllipse();

	// Function Class
	void Draw(HDC hdc, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); 
	Shape* Clone(); 
	string getClassName(); 
	vector<int> getRadius();
	Point getCenter();
	bool isIntersect(Line l);

	bool isPassThrough(Point D);
	bool isInsideEllipse(Point D);
	bool isOutsideEllipse(Point D);
};

