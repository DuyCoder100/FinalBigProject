#pragma once
#include "Point.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Shape
{
protected:
	Point m_LeftTop;
	Point m_RightBottom;
	int type;
public:
	//Constructor, Destructor
	Shape();
	~Shape();

	// Virtual function
	// virtual void Draw(HDC hdc, Point LeftTop, Point RightBottom) = 0;
	virtual void ReDraw(HDC hdc) = 0; // vẽ từ dữ liệu có sẵn của đối tượng
	virtual Shape* Clone() = 0; // Nhân bản đối tượng.
	virtual string getClassName() = 0;

	void setToaDo(Point LeftTop, Point RightBottom);
	int getType();
	Point GetFirstPoint();
	Point GetSecondPoint();
};