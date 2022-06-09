#include "stdafx.h"
#include "ShapeFactory.h"

// Constructor, Destructor
ShapeFactory::ShapeFactory()
{
}

ShapeFactory::~ShapeFactory()
{
}

Shape* ShapeFactory::GetObjectType(TypeShape _type)
{
	switch (_type)
	{
	case LINE: //1
	{
		return new CLine();
	}
	break;
	case RECTANGLE: //2
	{
		return new CRectangle();
	}
	break;
	case ELLIPSE: //3
	{
		return new CEllipse();
	}
	break;
	case SEMI_CIRCLE: //4
	{
		return new CSemiCircle();
	}
	case TRIANGLE: //5
	{
		return new CTriangle();
	}
	case PENTAGON: //6
	{
		return new CPentagon();
	}
	case HEXAGON: //7
	{
		return new CHexagon();
	}
	break;
	}
	return NULL;
}
