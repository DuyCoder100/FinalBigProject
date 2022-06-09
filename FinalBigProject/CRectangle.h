#pragma once
#include "Shape.h"

class CRectangle : public Shape
{
public:
	CRectangle();
	~CRectangle();

	// Function Class
	void Draw(HDC hdcPoint, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); 
	vector<Point> getVertexes();
	bool isIntersect(Line l);
	Shape* Clone(); 
	string getClassName(); 
};