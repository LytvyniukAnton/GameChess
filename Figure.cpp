#include "Figure.h"

Figure::Figure(Name name, Color color)
{
	this->name = name;
	this->color = color;
}

Figure::Color Figure::getColor() const
{
	return color;
}

Figure::Name Figure::getName() const
{
	return name;
}
