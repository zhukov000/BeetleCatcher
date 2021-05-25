#include "Beetle.h"

Beetle::Beetle(int _x, int _y, int _dx, int _dy, double _s): 
	pos(_x, _y), direction(_dx, _dy), speed(_s), step(0.0)
{ 
}

void Beetle::move() {
	step += speed;
	if (step > 1) {
		step = 0;
		pos.move(direction);
	}	
}

Point<int> Beetle::getPosition() {
	return pos;
}