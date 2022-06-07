#include "stdafx.h"
#include "CEllipse.h"

// Constructor, Destructor
CEllipse::CEllipse()
{
	type = 3;
}

CEllipse::~CEllipse() {}

void CEllipse::Draw(HDC hdc, Point LeftTop, Point RightBottom)
{
	// Lưu lại giá trị cho đối tượng để vẽ lần sau
	this->m_LeftTop = LeftTop;
	this->m_RightBottom = RightBottom;

	Ellipse(hdc, LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y);
}

void CEllipse::ReDraw(HDC hdc)
{
	this->Draw(hdc, this->m_LeftTop, this->m_RightBottom);
}

Shape* CEllipse::Clone()
{
	return new CEllipse();
}

string CEllipse::getClassName()
{
	return " CEllipse";
}

vector<int> CEllipse::getRadius()
{
	vector<int> radius(2);
	radius[0] = (this->m_RightBottom.x - this->m_LeftTop.x) / 2;
	radius[1] = (this->m_RightBottom.y - this->m_LeftTop.y) / 2;
	return radius;
}

Point CEllipse::getCenter()
{
	Point center;
	center.x = (this->m_LeftTop.x + this->m_RightBottom.x) / 2;
	center.y = (this->m_LeftTop.y + this->m_RightBottom.y) / 2;
	return center;
}

bool CEllipse::isInsideEllipse(Point E)
{
	vector<int> radius;
	double R1 = radius[0] * 1.0;
	double R2 = radius[1] * 1.0;

	Point center = getCenter();
	double x0 = center.x * 1.0;
	double y0 = center.y * 1.0;

	return ((E.x - x0) * (E.x - x0) / (R1 * R1) + (E.y - y0) * (E.y - y0) / (R2 * R2) - 1 < 0);
}

bool CEllipse::isPassThrough(Point E)
{
	vector<int> radius;
	double R1 = radius[0] * 1.0;
	double R2 = radius[1] * 1.0;

	Point center = getCenter();
	double x0 = center.x * 1.0;
	double y0 = center.y * 1.0;

	return ((E.x - x0) * (E.x - x0) / (R1 * R1) + (E.y - y0) * (E.y - y0) / (R2 * R2) - 1 == 0);
}

bool CEllipse::isOutsideEllipse(Point E)
{
	vector<int> radius;
	double R1 = radius[0] * 1.0;
	double R2 = radius[1] * 1.0;

	Point center = getCenter();
	double x0 = center.x * 1.0;
	double y0 = center.y * 1.0;

	return ((E.x - x0) * (E.x - x0) / (R1 * R1) + (E.y - y0) * (E.y - y0) / (R2 * R2) - 1 > 0);
}

bool CEllipse::isIntersect(Line l)
{
	//l: ax + by + c = 0 <=> y = (-a/b)x + (-c/b) <=> y = mx + n
	vector<int> coefs = l.getCoefs();
	double a = coefs[0] * 1.0;
	double b = coefs[1] * 1.0;
	double c = coefs[2] * 1.0;

	double m = -a / b;
	double n = -c / b;

	//E: (x - xO)^2 / R1^2 + (y - yO)^2 + R2^2 = 1
	vector<int> radius = getRadius();
	double R1 = radius[0] * 1.0;
	double R2 = radius[1] * 1.0;
	Point center = getCenter();
	double xO = center.x * 1.0;
	double yO = center.y * 1.0;

	double A = R2 * R2 + R1 * R1 * m * m;
	double B = 2 * (R1 * R1 * m * (n - yO) - R2 * R2 * xO);
	double C = R2 * R2 * xO * xO + R1 * R1 * (n - yO) * (n - yO) - R1 * R1 * R2 * R2;

	int roots = numberOfRootsOfQuadraticEquation(A, B, C);
	return (roots == 2);
}
