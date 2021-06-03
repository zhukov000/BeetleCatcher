#include "Scene.h"

Scene::Scene(unsigned width, unsigned height): 
	Frame(width, height), posCather(width/2, height/2), timeShoot(0), score(0)
{
	
}

void Scene::onPaint() {
	clear();

	// shoot background
	ULONGLONG current = GetTickCount64();
	if (current - timeShoot < 250) {
		for(int x = max(1, posCather.x - shootSize); x <= min(Width - 2, posCather.x + shootSize); ++x) {
			for (int y = max(1, posCather.y - shootSize); y <= min(Height - 2, posCather.y + shootSize); ++y) {
				consoleBuffer[getIndex(x, y)].Char.AsciiChar = ' ';
				consoleBuffer[getIndex(x, y)].Attributes = 0xfa;
			}
		}
	}
	// shoot cross
	consoleBuffer[getIndex(posCather.x, posCather.y)].Char.AsciiChar = '+';

	temp.clear();
	// beetles
	for (int i = 0; i < static_cast<int>(beetles.size()); ++i) {
		Point<int> p = beetles[i].getPosition();
		if ( onScene(p) )
		{
			consoleBuffer[getIndex(p.x, p.y)].Char.AsciiChar = '$';
			beetles[i].move();
			temp.push_back(beetles[i]);
		}
	}
	beetles.swap(temp);
}

bool Scene::onScene(Point<int> p) {
	return 0 < p.x && p.x < Width - 1 && 0 < p.y && p.y < Height;
}

void Scene::clear() {
	WORD attr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	for (unsigned i = 0; i < Height * Width; ++i) {
			consoleBuffer[i].Char.AsciiChar = ' ';
			consoleBuffer[i].Attributes = attr;
	}

	for (unsigned i = 0; i < Height; ++i) {
		consoleBuffer[getIndex(Width - 1, i)].Char.AsciiChar =
		consoleBuffer[getIndex(0, i)].Char.AsciiChar = (char)179;
	}

	for (unsigned i = 0; i < Width; ++i) {
		consoleBuffer[getIndex(i, 0)].Char.AsciiChar =
		consoleBuffer[getIndex(i, Height - 1)].Char.AsciiChar = (char)196;
	}

	consoleBuffer[getIndex(0, 0)].Char.AsciiChar = (char)218;
	consoleBuffer[getIndex(0, Height-1)].Char.AsciiChar = (char)192;
	consoleBuffer[getIndex(Width-1, Height-1)].Char.AsciiChar = (char)217;
	consoleBuffer[getIndex(Width-1, 0)].Char.AsciiChar = (char)191;

	std::ostringstream ostr;
	ostr << "Score: " << score;
	SetString(ostr.str(), { 55, 0 }, attr);
}

void Scene::shoot() {
	timeShoot = GetTickCount64();
	temp.clear();
	// beetles
	for (int i = 0; i < static_cast<int>(beetles.size()); ++i) {
		Point<int> p = beetles[i].getPosition();
		if (onScene(p))
		{
			if ( max(1, posCather.x - shootSize) <= p.x && p.x <= min(Width - 2, posCather.x + shootSize) 
				 && max(1, posCather.y - shootSize) <= p.y && p.y <= min(Height - 2, posCather.y + shootSize) ) { 
				score++;
			}
			else { 
				temp.push_back(beetles[i]);
			}
		}
	}
	beetles.swap(temp);
}

void Scene::beetleBorn() {
	int x = Rnd::genInt(10, Width - 10);
	int y = Rnd::genInt(10, Height - 10);

	int dx = Rnd::genInt(-1, 1);
	int dy = Rnd::genInt(-1, 1);

	double s = Rnd::genDouble(100);

	beetles.push_back({ x, y, dx, dy, s });
}

void Scene::up() {
	if (posCather.y > 1) posCather.y--;
}

void Scene::down() {
	if (posCather.y < Height - 2) posCather.y++;
}

void Scene::left() {
	if (posCather.x > 1) posCather.x--;
}

void Scene::right() {
	if (posCather.x < Width - 2) posCather.x++;
}