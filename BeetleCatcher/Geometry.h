#pragma once

template<typename T> class Vector;
template<typename T> class Point;

template<typename T>
class Point {

public:	
	Point() : x(0), y(0) {}
	Point(T _x, T _y) : x(_x), y(_y) {}

	void move(Vector<T> v) {
		x += v.x;
		y += v.y;
	}
	T x, y;
};

template<typename T>
class Vector {

public:

	Vector(): x(0), y(0) { }
	Vector(T _x, T _y) : x(_x), y(_y) { }
	explicit Vector(Point<T> p) : x(p.x), y(p.y) { }
	Vector(Point<T> p1, Point<T> p2) : x(p2.x - p1.x), y(p2.y - p1.y) { }

	T x, y;
};

