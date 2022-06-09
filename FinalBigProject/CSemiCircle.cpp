#include "stdafx.h"
#include "CSemiCircle.h"

CSemiCircle::CSemiCircle()
{
	type = 4;
}

CSemiCircle::~CSemiCircle() {}

void CSemiCircle::Draw(HDC hdc, Point LeftTop, Point RightBottom)
{
	mOldBrush = (HBRUSH)SelectObject(hdc, mBrush);

	this->m_LeftTop = LeftTop;
	this->m_RightBottom = RightBottom;

	int radius = (RightBottom.x - LeftTop.x) / 2;
	BeginPath(hdc);
	MoveToEx(hdc, LeftTop.x + radius, LeftTop.y, 0);
	LineTo(hdc, LeftTop.x, LeftTop.y);
	AngleArc(hdc, LeftTop.x, LeftTop.y, radius, 0, 180);
	LineTo(hdc, LeftTop.x + radius + 1, LeftTop.y);
	EndPath(hdc);
	StrokeAndFillPath(hdc);

	SelectObject(hdc, mOldBrush);
}

void CSemiCircle::ReDraw(HDC hdc)
{
	Draw(hdc, this->m_LeftTop, this->m_RightBottom);
}

Shape* CSemiCircle::Clone()
{
	return new CSemiCircle();
}

int CSemiCircle::getRadius()
{
	return (this->m_RightBottom.x - this->m_LeftTop.x) / 2;
}

Point CSemiCircle::getCenter()
{
	Point center;
	center.x = (this->m_LeftTop.x + this->m_RightBottom.x) / 2;
	center.y = (this->m_LeftTop.y + this->m_RightBottom.y) / 2;
	return center;
}

bool CSemiCircle::isPassThrough(Point D)
{
	int R = getRadius();
	Point O = getCenter();
	double xO = O.x * 1.0;
	double yO = O.y * 1.0;
	return ((D.x - xO) * (D.x - xO) + (D.y - yO) * (D.y - yO) - R * R == 0);
}

bool CSemiCircle::isInsideEllipse(Point D)
{
	int R = getRadius();
	Point O = getCenter();
	double xO = O.x * 1.0;
	double yO = O.y * 1.0;
	return ((D.x - xO) * (D.x - xO) + (D.y - yO) * (D.y - yO) - R * R < 0);
}

bool CSemiCircle::isOutsideEllipse(Point D)
{
	int R = getRadius();
	Point O = getCenter();
	double xO = O.x * 1.0;
	double yO = O.y * 1.0;
	return ((D.x - xO) * (D.x - xO) + (D.y - yO) * (D.y - yO) - R * R > 0);
}

bool CSemiCircle::isIntersect(Line l)
{
	//l: ax + by = c <=> y = (-a/b)x + c/b <=> y = mx + n
	vector<int> coefs = l.getCoefs();
	double a = coefs[0] * 1.0;
	double b = coefs[1] * 1.0;
	double c = coefs[2] * 1.0;

	double m = -a / b;
	double n = c / b;

	//E: (x - xO)^2 / R1^2 + (y - yO)^2 + R2^2 = 1
	int R = getRadius();
	
	Point center = getCenter();
	double xO = center.x * 1.0;
	double yO = center.y * 1.0;

	Point M;
	M.x = xO - R;
	M.y = yO;

	Point N;
	N.x = xO + R;
	N.y = yO;

	Line MN;
	MN.setToaDo(M, N);

	double A = m * m + 1;
	double B = 2 * (m * (n - yO) - xO);
	double C = xO * xO + (n - yO) * (n - yO) - R * R;

	int roots = numberOfRootsOfQuadraticEquation(A, B, C);
	if (roots == 2 && isOutsideEllipse(l.A) && isOutsideEllipse(l.B)) return true;
	if (roots == 1) return MN.isIntersect(l);
	return false;
}

string CSemiCircle::getClassName()
{
	return "Semi-circle";
}