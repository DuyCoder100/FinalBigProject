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

string CPentagon::getClassName()
{
	return "Pentagon";
}