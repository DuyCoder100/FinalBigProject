#pragma once
#include "Shape.h"
class CSemiCircle : public Shape
{
public:
	CSemiCircle();
	~CSemiCircle();

	void Draw(HDC hdc, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); // vẽ từ dữ liệu có sẵn của đối tượng
	Shape* Clone(); // Nhân bản đối tượng.
	string getClassName(); // Lấy tên của class
	int getRadius();
	Point getCenter();
	
	bool isPassThrough(Point D);
	bool isInsideEllipse(Point D);
	bool isOutsideEllipse(Point D);
	bool isIntersect(Line l);
};

