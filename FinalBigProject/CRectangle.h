#pragma once
#include "Shape.h"

class CRectangle : public Shape
{
public:
	CRectangle();
	~CRectangle();

	// Function Class
	void Draw(HDC hdcPoint, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); // vẽ từ dữ liệu có sẵn của đối tượng
	vector<Point> getVertexes();
	bool isIntersect(Line l);
	Shape* Clone(); // Nhân bản đối tượng.
	string getClassName(); // Lấy tên của class
};