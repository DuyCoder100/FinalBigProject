#pragma once
#include "Shape.h"

class CPentagon : public Shape
{
public:
	CPentagon();
	~CPentagon();

	// Function Class
	void Draw(HDC hdcPoint, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); // vẽ từ dữ liệu có sẵn của đối tượng
	Shape* Clone(); // Nhân bản đối tượng.
	string getClassName(); // Lấy tên của class 
};

