#pragma once
#include "Frame.h"
class Menu :
	public Frame
{
public:
	Menu(unsigned width = 0, unsigned height = 0);

	void onPaint() override;
	virtual void clear() override;

	int getPosition();
	virtual void up() override;
	virtual void down() override;

private:
	int position;
};


