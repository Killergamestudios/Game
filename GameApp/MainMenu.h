#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"

using namespace sf;

enum MainMenuState {opening,Main,newGame,LoadGame,Options,credits};

class MainMenu
{
public:
	MainMenu(RenderWindow &window);
	~MainMenu();
	void boot();

private:
	RenderWindow* m_window;
	MainMenuState m_state;
};

