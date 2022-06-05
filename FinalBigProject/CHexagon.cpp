#include "CHexagon.h"

CHexagon::CHexagon()
{
	type = 7;
}

CHexagon::~CHexagon() {}

void CHexagon::Draw(HDC hdc, Point LeftTop, Point RightBottom)
{
	this->m_LeftTop = LeftTop;
	this->m_RightBottom = RightBottom;

	POINT arr[6] = {};

	arr[0].x = (LeftTop.x + RightBottom.x) / 2;
	arr[0].y = LeftTop.y;

	arr[1].x = RightBottom.x;
	arr[1].y = LeftTop.y + (RightBottom.x - arr[0].x) * tanf(30 * 3.14 / 180);

	arr[2].x = RightBottom.x;
	arr[2].y = RightBottom.y - (RightBottom.x - arr[0].x) * tanf(30 * 3.14 / 180);

	arr[3].x = (LeftTop.x + RightBottom.x) / 2;
	arr[3].y = RightBottom.y;

	arr[4].x = LeftTop.x;
	arr[4].y = RightBottom.y - (RightBottom.x - arr[0].x) * tanf(30 * 3.14 / 180);

	Polygon(hdc, arr, 6);
}

void CHexagon::ReDraw(HDC hdc)
{
	this->Draw(hdc, this->m_LeftTop, this->m_RightBottom);
}