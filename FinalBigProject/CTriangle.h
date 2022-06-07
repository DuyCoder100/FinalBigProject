#pragma once
#include "Shape.h"

class CTriangle : public Shape
{
public:
	CTriangle();
	~CTriangle();

	// Function Class
	void Draw(HDC hdc, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); // vẽ từ dữ liệu có sẵn của đối tượng
	Shape* Clone(); // Nhân bản đối tượng.
	bool isIntersect(Line l);
	vector<Point> getVertexes();
	string getClassName(); // Lấy tên của class
};

