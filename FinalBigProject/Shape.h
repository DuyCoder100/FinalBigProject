#pragma once
#include "Point.h"
#include "Line.h"
#include "FinalBigPRoject.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
	Lop nay dung de ve cac doi tuong hinh hoc len ung dung Windows
*/
class Shape
{
protected:
	Point m_LeftTop;
	Point m_RightBottom;
	int type;
	HBRUSH mBrush;
	HBRUSH mOldBrush;
public:
	//Constructor, Destructor
	Shape();
	virtual ~Shape() {};
	bool isIntersected = false;
	int flag;
	// Virtual function
	virtual void ReDraw(HDC hdc) = 0; // Ve tu du lieu co san cua doi tuong
	virtual Shape* Clone() = 0; // Nhan ban doi tuong.
	virtual string getClassName() = 0;
	virtual bool isIntersect(Line l) = 0;
	void setColor(const LOGBRUSH& lb);
	void setToaDo(Point LeftTop, Point RightBottom);
	int getType();
	Point GetFirstPoint();
	Point GetSecondPoint();
};