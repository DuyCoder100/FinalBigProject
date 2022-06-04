#include "stdafx.h"
#include "CRectangle.h"


CRectangle::CRectangle()
{
	type = 2;
}

CRectangle::~CRectangle() {}

void CRectangle::Draw(HDC hdc, Point LeftTop, Point RightBottom)
{
	// Lưu lại giá trị cho đối tượng để vẽ lần sau
	this->m_LeftTop = LeftTop;
	this->m_RightBottom = RightBottom;

	//HDC hdc = GetDC(hwnd); // Lấy hdc từ handle

	Rectangle(hdc, LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y);

	//ReleaseDC(hwnd, hdc); // Giải phóng hdc vừa lấy từ handle
}

void CRectangle::ReDraw(HDC hdc)
{
	this->Draw(hdc, this->m_LeftTop, this->m_RightBottom);
}

Shape* CRectangle::Clone()
{
	return new CRectangle();
}

string CRectangle::getClassName()
{
	return "CRectangle";
}
