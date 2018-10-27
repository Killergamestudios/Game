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
	int menu();
	

private:
	void setText();
	void draw();
	bool actions(int optionSelected, int &indexFileToLoad);

	Font font;
	RenderWindow* m_window;
	MainMenuState m_state;
	vector<Text> textArray;
	vector<string> texts;
};

