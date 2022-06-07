#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class Point
{
public:
	int x; // hoành độ
	int y; // tung độ
	Point();
	~Point();

	int getPosRectBetwTwoPoint(const Point& A);
};

int numberOfRootsOfQuadraticEquation(double a, double b, double c);