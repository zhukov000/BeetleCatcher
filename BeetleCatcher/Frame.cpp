#include "Frame.h"

Frame::Frame(unsigned width, unsigned height) : Width(width), Height(height), consoleBuffer(nullptr) {
	if (Width + Height > 0) {
		consoleBuffer = (CHAR_INFO*)calloc(Width * Height, sizeof(CHAR_INFO));
	}	
}

Frame::Frame(const Frame& other) {
	Width = other.Width;
	Height = other.Height;

	consoleBuffer = (CHAR_INFO*)calloc(Width * Height, sizeof(CHAR_INFO));
	if (consoleBuffer) {
		memcpy(consoleBuffer, other.consoleBuffer, Width * Height * sizeof(CHAR_INFO));
	}
}

Frame& Frame::operator=(const Frame& other) {
	if (Width + Height > 0) {
		free(consoleBuffer);
	}

	Width = other.Width;
	Height = other.Height;

	consoleBuffer = (CHAR_INFO*)calloc(Width * Height, sizeof(CHAR_INFO));
	if (consoleBuffer) {
		memcpy(consoleBuffer, other.consoleBuffer, Width * Height * sizeof(CHAR_INFO));
	}

	return *this;
}

Frame::~Frame() {
	if (Width + Height > 0) {
		free(consoleBuffer);
	}
}

void Frame::SetString(string text, COORD pos, WORD chattr) {
	unsigned x = pos.X, y = pos.Y;
	for (unsigned i = 0, st = x + Width * y; i < text.size(); ++i, ++st)
	{
		consoleBuffer[st].Char.AsciiChar = text[i];
		consoleBuffer[st].Attributes = chattr;
	}
}

void Frame::SetChar(char ch, COORD pos, WORD chattr) {
	consoleBuffer[pos.X + Width * pos.Y].Char.AsciiChar = ch;
	consoleBuffer[pos.X + Width * pos.Y].Attributes = chattr;
}

CHAR_INFO* Frame::buffer() {
	return consoleBuffer;
}

COORD Frame::size() {
	return {(short)Width, (short)Height};
}

void Frame::onPaint() {
	// do nothing
	clear();
	WORD chAttr = FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetString("I mustn't be here", { 22, 8 }, chAttr);
}

void Frame::clear() {
	for (unsigned i = 0; i < Width * Height; ++i) {
		consoleBuffer[i].Char.AsciiChar = ' ';
		consoleBuffer[i].Attributes = 0;
	}	
}

int Frame::getIndex(int x, int y) {
	return x + y * Width;
}

void Frame::up() {
	// do nothing
}
void Frame::down() {
	// do nothing
}
void Frame::left() {
	// do nothing
}
void Frame::right() {
	// do nothing
}