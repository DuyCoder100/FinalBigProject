#include "stdafx.h"
#include "CSemiCircle.h"

CSemiCircle::CSemiCircle()
{
	type = 4;
}

CSemiCircle::~CSemiCircle() {}

void CSemiCircle::Draw(HDC hdc, Point LeftTop, Point RightBottom)
{
	this->m_LeftTop = LeftTop;
	this->m_RightBottom = RightBottom;

	LONG radius = (RightBottom.x - LeftTop.x) / 2;
	MoveToEx(hdc, LeftTop.x + radius, LeftTop.y, 0);
	LineTo(hdc, LeftTop.x, LeftTop.y);
	AngleArc(hdc, LeftTop.x, LeftTop.y, radius, 0, 180);
	LineTo(hdc, LeftTop.x + radius, LeftTop.y);
}

void CSemiCircle::ReDraw(HDC hdc)
{
	Draw(hdc, this->m_LeftTop, this->m_RightBottom);
}

Shape* CSemiCircle::Clone()
{
	return new CSemiCircle();
}

string CSemiCircle::getClassName()
{
	return "Semi-circle";
}