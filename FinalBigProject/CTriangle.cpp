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

vector<Point> CTriangle::getVertexes()
{
	vector<Point> points(3);
	points[0].x = this->m_LeftTop.x;
	points[0].y = this->m_RightBottom.y;

	points[1].x = (this->m_LeftTop.x + this->m_RightBottom.x) / 2;
	points[1].y = this->m_LeftTop.y;

	points[2].x = this->m_RightBottom.x;
	points[2].y = this->m_RightBottom.y;
	return points;
}

bool CTriangle::isIntersect(Line l)
{
	vector<Point> points = getVertexes();
	Point A = points[0];
	Point B = points[1];
	Point C = points[2];

	int count = 0;
	Line AB;
	AB.setToaDo(A, B);
	if (AB.isIntersect(l)) ++count;
	Line BC;
	BC.setToaDo(B, C);
	if (BC.isIntersect(l)) ++count;
	Line CA;
	CA.setToaDo(C, A);
	if (CA.isIntersect(l)) ++count;
	return (count == 2 && !l.isBetween(A) && !l.isBetween(B) && !l.isBetween(C));
}

string CTriangle::getClassName()
{
	return "Triangle";
}