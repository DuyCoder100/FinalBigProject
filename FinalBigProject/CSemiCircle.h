#pragma once
#include "Shape.h"
class CSemiCircle : public Shape
{
public:
	CSemiCircle();
	~CSemiCircle();

	void Draw(HDC hdc, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); 
	Shape* Clone(); 
	string getClassName(); 
	int getRadius();
	Point getCenter();
	
	bool isOutsideSemiCircle(Point D);
	bool isIntersect(Line l);
};

