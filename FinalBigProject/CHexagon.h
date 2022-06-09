#pragma once
#include "Shape.h"

class CHexagon : public Shape
{
public:
	CHexagon();
	~CHexagon();

	// Function Class
	void Draw(HDC hdcPoint, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); 
	Shape* Clone(); 
	vector<Point> getVertexes();
	bool isIntersect(Line l);
	string getClassName(); 
};

