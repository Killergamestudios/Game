#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Core/textureHolder.h"
#include "fstream"
#include "../Core/Controller.h"
#include "Theme/Theme.h"
class GameMenu
{
public:
	GameMenu(RenderWindow &window);
	~GameMenu();

	virtual void init() = 0;
	virtual void update(float&) = 0;
	virtual void draw() = 0;
	virtual void input() = 0;
	virtual void actions() = 0;
	virtual void mouseInput(Vector2i);

protected:
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

