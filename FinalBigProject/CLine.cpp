#include "stdafx.h"
#include "CLine.h"

// Constructor, Destructor
CLine::CLine()
{
	type = 1;
}

CLine::~CLine()
{
}

void CLine::Draw(HDC hdc, Point LeftTop, Point RightBottom)
{
	// Lưu lại giá trị cho đối tượng để vẽ lần sau
	this->m_LeftTop = LeftTop;
	this->m_RightBottom = RightBottom;

	// Vẽ đoạn thẳng từ tọa độ LeftTop -> RightBottom
	MoveToEx(hdc, LeftTop.x, LeftTop.y, NULL);
	LineTo(hdc, RightBottom.x, RightBottom.y);

	//ReleaseDC(hwnd, hdc);
}

void CLine::ReDraw(HDC hdc)
{
	this->Draw(hdc, this->m_LeftTop, this->m_RightBottom);
}

Shape* CLine::Clone()
{
	return new CLine();
}

string CLine::getClassName()
{
	return "CLine";
}
