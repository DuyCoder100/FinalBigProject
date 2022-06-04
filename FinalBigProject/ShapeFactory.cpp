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
	case LINE:
	{
		return new CLine();
	}
	break;
	case RECTANGLE:
	{
		return new CRectangle();
	}
	break;
	case ELLIPSE:
	{
		return new CEllipse();
	}
	break;
	case SEMI_CIRCLE:
	{
		return new CSemiCircle();
	}
	case TRIANGLE:
	{
		return new CTriangle();
	}
	break;
	}
	return NULL;
}
