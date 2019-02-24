#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "textureHolder.h"
#include "fstream"
#include "Controller.h"
#include "Theme.h"
class GameMenu
{
public:
	GameMenu(RenderWindow &window);
	~GameMenu();

	virtual void init() = 0;
	virtual void update(float) = 0;
	virtual void draw() = 0;
	virtual void input() = 0;
	virtual void actions() = 0;
	
	Font font; // Global font for main menu text
	RenderWindow* m_window; // DONT DELETE

	map<int, Drawable*> drawStack; // a set with the order in which graphics render
	/*
		DrawStack Ordering:
		0: Background
		1: Background Secondary
		2: Main Content
		3: Main Content Secondary
		4: Alerts, Popups etc
	*/

	map<int, pair<string, Drawable*>> tabOrder; // a set with the order in which you can select elements
};

