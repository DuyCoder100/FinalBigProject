#pragma once

#include <vector>
#include "CLine.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CSemiCircle.h"
#include "CTriangle.h"

#define SHAPE_LINE 0
#define SHAPE_RECTANGLE 1
#define SHAPE_ELLIPSE 2
#define SHAPE_SEMI_CIRCLE 3
#define SHAPE_TRIANGLE 4
#define SHAPE_PENTAGON 5
#define SHAPE_HEXAGON 6


class ShapePrototype
{
private:
	vector<Shape*> m_Model;
	int m_curShapeType;
public:
	// Constructor 
	ShapePrototype();
	~ShapePrototype();

	//Function
	bool setCurShapeType(int curShapeType);

	int getCurShapeType();

	bool addModel(Shape* model);

	Shape* createNewObject();	// Tao mot doi tuong moi theo shape hien hanh.
};