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

	Chord(hdc, LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y,
		LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y);
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