#include "Game.h"

Game::Game(string title, COORD size) {
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	std::tie(wWidth, wHeight) = std::tie(size.X, size.Y);

	SetConsoleTitle(std::wstring(title.begin(), title.end()).c_str());
	
	SMALL_RECT windowSize = { 0, 0, wWidth - 1, wHeight - 1 };
	COORD bufferSize = { wWidth, wHeight };

	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	openMenu();
}

Game::~Game() {
	if (curFrame) 
		delete curFrame;
}

void Game::start() {

	double prob = 0.1;

	while (status != GAMESTATUS::EXIT) {
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(50ms);

		if (status == GAMESTATUS::PLAY) {
			if (prob < 0.3) prob += 0.01;
			if (Rnd::genDouble(1000) < prob) {
				prob = prob / 2.0;
				((Scene *)curFrame)->beetleBorn();
			}
		}
		else { 
			prob = 0.1;
		}

		paint();

		INPUT_RECORD* eventBuffer;
		DWORD numEventsRead = getInput(&eventBuffer);

		for (int i = 0; i < numEventsRead; ++i) {
			switch (eventBuffer[i].EventType) {
			case KEY_EVENT:
				KeyEventProc(eventBuffer[i].Event.KeyEvent);
				break;
			
			case MOUSE_EVENT: 
				MouseEventProc(eventBuffer[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT:

			case FOCUS_EVENT:  
			
			case MENU_EVENT:   
				break;
			
			default:
				ErrorExit("Unknown event type");
				break;
			}
		}	
	}
}

void Game::paint() {
	curFrame->onPaint();

	SMALL_RECT consoleWriteArea = { 0, 0, wWidth - 1, wHeight - 1 };
	WriteConsoleOutputA(wHnd, curFrame->buffer(), curFrame->size(), { 0, 0 }, &consoleWriteArea);
}

DWORD Game::getInput(INPUT_RECORD** eventBuffer) {
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;

	GetNumberOfConsoleInputEvents(rHnd, &numEvents);

	if (numEvents) {
		*eventBuffer = (INPUT_RECORD*) malloc(sizeof(INPUT_RECORD) * numEvents);
		ReadConsoleInput(rHnd, *eventBuffer, numEvents, &numEventsRead);
	}

	return numEventsRead;
}

void Game::ErrorExit(string message) {
	fprintf(stderr, "%s\n", message.c_str());
	ExitProcess(0);
}

void Game::KeyEventProc(KEY_EVENT_RECORD ker) {
	switch (ker.wVirtualKeyCode) {
	case VK_ESCAPE:
		if (status == GAMESTATUS::MENU) status = GAMESTATUS::EXIT;
		break;
	case VK_UP:
		curFrame->up();
		break;
	case VK_DOWN:
		curFrame->down();
		break;
	case VK_LEFT:
		curFrame->left();
		break;
	case VK_RIGHT:
		curFrame->right();
		break;
	case 's':
	case 'S':
		play();
		break;
	case 'q':
	case 'Q':
		if (status == GAMESTATUS::PLAY) openMenu();
		break;
	case VK_RETURN:
		if (status == GAMESTATUS::MENU) {
			if (((Menu*)curFrame)->getPosition())
				status = GAMESTATUS::EXIT;
			else
				play();
		}
		else {
			((Scene*)curFrame)->shoot();
		}
		break;
	}
}

void Game::openMenu() {
	if (curFrame) 
		delete curFrame;

	curFrame = new Menu(wWidth, wHeight);
	status = GAMESTATUS::MENU;
}

void Game::play() {
	if (curFrame)
		delete curFrame;

	curFrame = new Scene(wWidth, wHeight);
	status = GAMESTATUS::PLAY;
}

void Game::MouseEventProc(MOUSE_EVENT_RECORD) {
	// do nothing
}