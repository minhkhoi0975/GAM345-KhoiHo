#pragma once

#include <string>
#include <vector>
#include "Vector2.h"

struct Stroke
{
	// The name of the stroke
	std::string name;

	// The points of the stroke
	std::vector<Vector2> points;

	// Assignment operator overload.
	Stroke& operator= (const Stroke& other);
};

