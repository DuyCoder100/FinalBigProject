#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

/*
	Lop nay dung de luu thong tin toa do cua 1 diem.
*/
class Point
{
public:
	int x; // Hoanh do
	int y; // Tung do
	Point();
	~Point();

	int getPosRectBetwTwoPoint(const Point& A);
};

int numberOfRootsOfQuadraticEquation(double a, double b, double c);