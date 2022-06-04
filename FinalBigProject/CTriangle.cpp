#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle()
{
	type = 5;
}

CTriangle::~CTriangle() {}

void CTriangle::Draw(HDC hdc, Point LeftTop, Point RightBottom)
{
	// Lưu lại giá trị cho đối tượng để vẽ lần sau
	this->m_LeftTop = LeftTop;
	this->m_RightBottom = RightBottom;

	//HDC hdc = GetDC(hwnd); // Lấy hdc từ handle
	POINT arr[3] = {};
	arr[0].x = LeftTop.x;
	arr[0].y = RightBottom.y;

	arr[1].x = (LeftTop.x + RightBottom.x) / 2;
	arr[1].y = LeftTop.y;

	arr[2].x = RightBottom.x;
	arr[2].y = RightBottom.y;
	Polygon(hdc, arr, 3);

	//ReleaseDC(hwnd, hdc); // Giải phóng hdc vừa lấy từ handle
}

void CTriangle::ReDraw(HDC hdc)
{
	this->Draw(hdc, this->m_LeftTop, this->m_RightBottom);
}

Shape* CTriangle::Clone()
{
	return new CTriangle();
}

string CTriangle::getClassName()
{
	return "Triangle";
}