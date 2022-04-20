#pragma once

#include <string>
#include <vector>
#include "Vector2.h"

class Stroke
{
public:
	// Constructors.
	Stroke();
	Stroke(const Stroke& other);

	// The name of the stroke
	std::string name;

	// The points of the stroke
	std::vector<Vector2> points;

	// Assignment operator overloading.
	Stroke& operator= (const Stroke& other);

	// Equal operator overloading.
	bool operator== (const Stroke& other);
};

