#include "Menu.h"

Menu::Menu(unsigned width, unsigned height) : Frame(width, height), position(0) {

}

void Menu::onPaint() {
	clear();
	WORD chAttr = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetString("Beetle Catcher v.1.0", { 22, 8 }, chAttr);
	SetChar('>', { 20, 12 + 2 * (short)position }, chAttr);
	SetString("Play", { 25, 12 }, chAttr);
	SetString("Exit", { 25, 14 }, chAttr);
}

int Menu::getPosition() {
	return position;
}

void Menu::up() {
	position = 0;
}

void Menu::down() {
	position = 1;
}

void Menu::clear() {
	Frame::clear();
}