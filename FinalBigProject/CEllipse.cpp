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
