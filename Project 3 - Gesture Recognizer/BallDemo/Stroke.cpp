#include "Stroke.h"

Stroke& Stroke::operator=(const Stroke& other)
{
	this->name = other.name;
	this->points = other.points;

	return *this;
}
