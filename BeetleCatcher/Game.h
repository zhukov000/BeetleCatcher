#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>
#include <tuple>
#include <thread>
#include <chrono>

#include "Frame.h"
#include "Menu.h"
#include "Scene.h"
#include "Tools.h"

using std::string;

class Game
{
	enum class GAMESTATUS { MENU = 0, PLAY, EXIT };

public:
	Game(string title = "Beetle Catcher", COORD size = {70, 35});
	virtual ~Game();

	void start();

	void paint();

	void openMenu();

	void play();

	DWORD getInput(INPUT_RECORD**);

	void KeyEventProc(KEY_EVENT_RECORD);

	void MouseEventProc(MOUSE_EVENT_RECORD);

	void ErrorExit(string);

private:
	/* write/read handle */
	HANDLE wHnd, rHnd;
	/* window size */
	unsigned wWidth, wHeight;

	GAMESTATUS status;

	Frame *curFrame;
};

