#pragma once
#include "Shape.h"

class CEllipse : public Shape
{
public:
	// Constructor, Destructor
	CEllipse();
	~CEllipse();

	// Function Class
	void Draw(HDC hdc, Point LeftTop, Point RightBottom);
	void ReDraw(HDC hdc); // vẽ từ dữ liệu có sẵn của đối tượng
	Shape* Clone(); // Nhân bản đối tượng.
	string getClassName(); // Lấy tên của class
};