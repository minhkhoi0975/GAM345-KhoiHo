#include "Stroke.h"

Stroke::Stroke():name(std::string())
{
}

Stroke::Stroke(const Stroke& other):name(other.name), points(other.points)
{
}

Stroke& Stroke::operator=(const Stroke& other)
{
	this->name = other.name;
	this->points = other.points;

	return *this;
}

bool Stroke::operator==(const Stroke& other)
{
	return this->name == other.name && this->points == other.points;
}
