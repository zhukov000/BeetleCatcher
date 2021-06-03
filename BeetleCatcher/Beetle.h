#pragma once

#include "Geometry.h"

class Beetle {

public:
	Beetle(int, int, int, int, double);
	
	void move();

	Point<int> getPosition();

private:
	Point<int> pos;
	Vector<int> direction;
	double speed, step;
};

