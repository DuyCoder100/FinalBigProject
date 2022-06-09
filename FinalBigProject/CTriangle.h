#pragma once
#include "Shape.h"

class CTriangle : public Shape
{
public:
	CTriangle();
	~CTriangle();

	// Function Class
	void Draw(HDC hdc, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); 
	Shape* Clone(); 
	bool isIntersect(Line l);
	vector<Point> getVertexes();
	string getClassName(); 
};

