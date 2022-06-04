#pragma once
#include "Shape.h"

class CLine : public Shape
{
public:
	// Constructor, Destructor
	CLine();
	~CLine();

	// Function Class
	void Draw(HDC hdc, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); // vẽ từ dữ liệu có sẵn của đối tượng
	Shape* Clone(); // Nhân bản đối tượng.
	string getClassName(); // Lấy tên của class
};