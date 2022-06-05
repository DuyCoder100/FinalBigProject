#include "stdafx.h"
#include "ShapePrototype.h"

// Constructor, Destructor
ShapePrototype::ShapePrototype()
{
	m_curShapeType = SHAPE_LINE;
}

ShapePrototype::~ShapePrototype()
{
	for (int i = 0; i < this->m_Model.size(); i++) {
		delete[] this->m_Model[i];
	}
}


// Function
bool ShapePrototype::setCurShapeType(int curShapeType)
{
	if (curShapeType >= 0 && curShapeType <= 6)
	{
		this->m_curShapeType = curShapeType;
		return true;
	}
	return false;
}

int ShapePrototype::getCurShapeType()
{
	return this->m_curShapeType;
}

bool ShapePrototype::addModel(Shape* model)
{
	for (int i = 0; i < this->m_Model.size(); i++) {
		if (this->m_Model[i]->getClassName() == model->getClassName()) {
			return false;
		}
	}
	this->m_Model.push_back(model);
	return true;
}

Shape* ShapePrototype::createNewObject()
{
	if (this->m_curShapeType < this->m_Model.size()) {
		return this->m_Model[this->m_curShapeType]->Clone();
	}
	return NULL;
}