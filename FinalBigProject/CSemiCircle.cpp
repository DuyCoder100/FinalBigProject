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
	MoveToEx(hdc, LeftTop.x, RightBottom.y, 0);
	AngleArc(hdc, LeftTop.x, RightBottom.y, radius, 0, 180);
	LineTo(hdc, LeftTop.x, RightBottom.y);
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
	return abs(this->m_RightBottom.x - this->m_LeftTop.x) / 2;
}

Point CSemiCircle::getCenter()
{
	Point center;
	center.x = (this->m_LeftTop.x + this->m_RightBottom.x) / 2;
	center.y = this->m_RightBottom.y;
	return center;
}

bool CSemiCircle::isOutsideSemiCircle(Point D)
{
	double R = getRadius() * 1.0;
	Point O = getCenter();
	double xO = O.x * 1.0;
	double yO = O.y * 1.0;

	Point M;
	M.x = this->m_LeftTop.x;
	M.y = this->m_RightBottom.y;

	Point N;
	N.x = this->m_RightBottom.x;
	N.y = this->m_RightBottom.y;

	Line MN;
	MN.setToaDo(M, N);
	vector<int> coefs = MN.getCoefs();
	double A = coefs[0] * 1.0;
	double B = coefs[1] * 1.0;
	double C = -coefs[2] * 1.0;
	return !((D.x - xO) * (D.x - xO) + (D.y - yO) * (D.y - yO) - R * R < 0
		&& A * D.x + B * D.y + C > 0);
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
	//E: (x - xO)^2 + (y - yO)^2 = R^2
	double R = getRadius() * 1.0;

	Point center = getCenter();
	double xO = center.x * 1.0;
	double yO = center.y * 1.0;

	Point M;
	M.x = this->m_LeftTop.x;
	M.y = this->m_RightBottom.y;

	Point N;
	N.x = this->m_RightBottom.x;
	N.y = this->m_RightBottom.y;

	double A = m * m + 1;
	double B = 2 * (m * (n - yO) - xO);
	double C = xO * xO + (n - yO) * (n - yO) - R * R;

	double delta = B * B - 4 * A * C;
	if (delta >= 0)
	{
		double x1 = (-b - sqrt(delta)) / (2 * a);
		double x2 = (-b + sqrt(delta)) / (2 * a);
		if (M.x < N.x)
		{
			if (((m * x1 + n) < yO) || (m * x2 + n) < yO)
			{
				return true;
			}
		}
		if (M.x > N.x)
		{
			if (((m * x1 + n) > yO) || (m * x2 + n) > yO)
			{
				return true;
			}
		}
		if (M.y < N.y)
		{
			if (x1 > xO || x2 > xO)
			{
				return true;
			}
		}
		if (M.y > N.y)
		{
			if (x1 < xO || x2 < xO)
			{
				return true;
			}
		}
	}
	return false;
}

string CSemiCircle::getClassName()
{
	return "Semi-circle";
}