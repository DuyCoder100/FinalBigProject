#pragma once
#include "Point.h"

//Lop nay dung de xu ly bai toan giao giua cac hinh va duong thang.
class Line
{
public:
	Point A;
	Point B;
	
	Line() {};
	~Line() {};
	vector<int> getCoefs();
	void setToaDo(Point D, Point E);
	bool isIntersect(Line l);
	bool isPassThrough(Point P);
};
