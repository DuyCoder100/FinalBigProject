#include "Line.h"

vector<int> Line::getCoefs()
{
	vector<int> coefs(3);
	coefs[0] = B.y - A.y;
	coefs[1] = A.x - B.x;
	coefs[2] = coefs[0] * A.x + coefs[1] * A.y;
	return coefs;
}

void Line::setToaDo(Point D, Point E)
{
	A = D;
	B = E;
}

bool Line::isIntersect(Line l)
{
	vector<int> coefs_1 = getCoefs();
	vector<int> coefs_2 = l.getCoefs();

	//A1x + B1y = C1
	double A1 = coefs_1[0] * 1.0;
	double B1 = coefs_1[1] * 1.0;
	double C1 = coefs_1[2] * 1.0;

	//A2x + B2y = C2
	double A2 = coefs_2[0] * 1.0;
	double B2 = coefs_2[1] * 1.0;
	double C2 = coefs_2[2] * 1.0;

	double denominator = A1 * B2 - A2 * B1;

	if (denominator == 0) return false;

	double X_intercept = (B2 * C1 - B1 * C2) * 1.0 / denominator;
	double Y_intercept = (A1 * C2 - A2 * C1) * 1.0 / denominator;

	double rX1 = (X_intercept - A.x * 1.0) / (B.x * 1.0 - A.x * 1.0);
	double rY1 = (Y_intercept - A.y * 1.0) / (B.y * 1.0 - A.y * 1.0);

	double rX2 = (X_intercept - l.A.x * 1.0) / (l.B.x * 1.0 - l.A.x * 1.0);
	double rY2 = (Y_intercept - l.A.y * 1.0) / (l.B.y * 1.0 - l.A.y * 1.0);

	return (((rX1 >= 0 && rX1 <= 1) || (rY1 >= 0 && rY1 <= 1)) &&
		((rX2 >= 0 && rX2 <= 1) || (rY2 >= 0 && rY2 <= 1)));
}

bool Line::isBetween(Point P)
{
	vector<int> coefs = getCoefs();
	return (coefs[0] * P.x + coefs[1] * P.y + coefs[2] == 0 &&
		(this->A.x <= P.x && P.x <= this->B.x) &&
		(this->A.y <= P.y && P.y <= this->B.y));
}