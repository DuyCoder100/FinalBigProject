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

vector<Point> CRectangle::getVertexes()
{
	vector<Point> points(4);
	points[0].x = this->m_LeftTop.x;
	points[0].y = this->m_LeftTop.y;

	points[1].x = this->m_RightBottom.x;
	points[1].y = this->m_LeftTop.y;

	points[2].x = this->m_RightBottom.x;
	points[2].y = this->m_RightBottom.y;

	points[3].x = this->m_LeftTop.x;
	points[3].y = this->m_RightBottom.y;

	return points;
}

bool CRectangle::isIntersect(Line l)
{
	vector<Point> points = getVertexes();
	Point A = points[0];
	Point B = points[1];
	Point C = points[2];
	Point D = points[3];

	int count = 0;
	Line AB;
	AB.setToaDo(A, B);
	if (AB.isIntersect(l)) ++count;
	Line BC;
	BC.setToaDo(B, C);
	if (BC.isIntersect(l)) ++count;
	Line CD;
	CD.setToaDo(C, D);
	if (CD.isIntersect(l)) ++count;
	Line DA;
	DA.setToaDo(D, A);
	if (DA.isIntersect(l)) ++count;

	return (count == 2);
}

string CRectangle::getClassName()
{
	return "CRectangle";
}
