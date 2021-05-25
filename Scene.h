#pragma once
#include <vector>
#include <sstream>
#include "Frame.h"
#include "Geometry.h"
#include "Beetle.h"
#include "Tools.h"

using std::vector;

class Scene :
	public Frame
{
public:
	Scene(unsigned width = 0, unsigned height = 0);

	void onPaint() override;

	virtual void clear() override;

	void beetleBorn();

	void shoot();

	virtual void up() override;

	virtual void down() override;

	virtual void left() override;

	virtual void right() override;

	bool onScene(Point<int>);

private:
	vector<Beetle> beetles, temp;

	Point<int> posCather;

	ULONGLONG timeShoot;
	
	int score;

	const int shootSize = 3;
};

