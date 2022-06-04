#pragma once
class Point
{
public:
	int x; // hoành độ
	int y; // tung độ
	Point();
	~Point();

	int getPosRectBetwTwoPoint(const Point& A);
};