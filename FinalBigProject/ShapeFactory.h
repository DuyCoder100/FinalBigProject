#pragma once
#include "CLine.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CSemiCircle.h"
#include "CTriangle.h"
#include "CPentagon.h"
#include "CHexagon.h"

enum TypeShape {
	LINE,
	RECTANGLE,
	ELLIPSE,
	SEMI_CIRCLE,
	TRIANGLE,
	PENTAGON,
	HEXAGON
};

class ShapeFactory
{
public:
	// Constructor, Destructor
	ShapeFactory();
	~ShapeFactory();

	static Shape* GetObjectType(TypeShape _type);
};

