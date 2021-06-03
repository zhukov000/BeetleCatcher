#pragma once

#include <windows.h>
#include <string>

using std::string;

class Frame
{
public:
	Frame(unsigned width = 0, unsigned height = 0);
	Frame(const Frame& other);
	Frame& operator=(const Frame& other);

	virtual ~Frame();

	virtual void onPaint();

	virtual void clear();

	void SetString(string text, COORD pos, WORD chattr = 0xFF);

	void SetChar(char ch, COORD pos, WORD chattr = 0xFF);
	
	CHAR_INFO* buffer();

	COORD size();

	virtual int getIndex(int, int);
	
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();

protected:
	unsigned Width, Height;
	CHAR_INFO* consoleBuffer;

private:

};

