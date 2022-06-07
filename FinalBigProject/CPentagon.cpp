#include "CPentagon.h"

CPentagon::CPentagon()
{
	type = 6;
}

CPentagon::~CPentagon() {}

void CPentagon::Draw(HDC hdc, Point LeftTop, Point RightBottom)
{
	// Lưu lại giá trị cho đối tượng để vẽ lần sau
	this->m_LeftTop = LeftTop;
	this->m_RightBottom = RightBottom;

	POINT arr[5] = {};
	
	arr[0].x = (LeftTop.x + RightBottom.x) / 2;
	arr[0].y = LeftTop.y;

	arr[1].x = RightBottom.x;
	arr[1].y = LeftTop.y + (RightBottom.x - arr[0].x) * tanf(36 * 3.14 / 180);

	arr[2].x = RightBottom.x - (RightBottom.y - arr[1].y) * 1 / tanf(72 * 3.14 / 180);
	arr[2].y = RightBottom.y;

	arr[3].x = LeftTop.x + (RightBottom.y - arr[1].y) * 1 / tanf(72 * 3.14 / 180);
	arr[3].y = RightBottom.y;

	arr[4].x = LeftTop.x;
	arr[4].y = LeftTop.y + (RightBottom.x - arr[0].x) * tanf(36 * 3.14 / 180);

	Polygon(hdc, arr, 5);
}

void CPentagon::ReDraw(HDC hdc)
{
	this->Draw(hdc, this->m_LeftTop, this->m_RightBottom);
}

Shape* CPentagon::Clone()
{
	return new CPentagon();
}

vector<Point> CPentagon::getVertexes()
{
	vector<Point> points(5);
	points[0].x = (this->m_LeftTop.x + this->m_RightBottom.x) / 2;
	points[0].y = this->m_LeftTop.y;

	points[1].x = this->m_RightBottom.x;
	points[1].y = this->m_LeftTop.y +
		(this->m_RightBottom.x - points[0].x) * tanf(36 * 3.14 / 180);

	points[2].x = this->m_RightBottom.x -
		(this->m_RightBottom.y - points[1].y) * 1 / tanf(72 * 3.14 / 180);
	points[2].y = this->m_RightBottom.y;

	points[3].x = this->m_LeftTop.x +
		(this->m_RightBottom.y - points[1].y) * 1 / tanf(72 * 3.14 / 180);
	points[3].y = this->m_RightBottom.y;

	points[4].x = this->m_LeftTop.x;
	points[4].y = this->m_LeftTop.y +
		(this->m_RightBottom.x - points[0].x) * tanf(36 * 3.14 / 180);

	return points;
}

bool CPentagon::isIntersect(Line l)
{
	vector<Point> points = getVertexes();
	Point A = points[0];
	Point B = points[1];
	Point C = points[2];
	Point D = points[3];
	Point E = points[4];

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
	Line DE;
	DE.setToaDo(D, E);
	if (DE.isIntersect(l)) ++count;
	Line EA;
	EA.setToaDo(E, A);
	if (EA.isIntersect(l)) ++count;

	return (count == 2);
}

string CPentagon::getClassName()
{
	return "Pentagon";
}