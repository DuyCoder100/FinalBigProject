#pragma once
#include "Shape.h"

class CHexagon : public Shape
{
public:
	CHexagon();
	~CHexagon();

	// Function Class
	void Draw(HDC hdcPoint, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); // vẽ từ dữ liệu có sẵn của đối tượng
	Shape* Clone(); // Nhân bản đối tượng.
	string getClassName(); // Lấy tên của class 
};

