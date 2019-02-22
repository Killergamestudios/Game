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
	
	struct CustomCompare
	{
		bool operator()(const pair<int, Drawable*> left, const pair<int, Drawable*> right)
		{
			return (left.first < right.first);
		}
	};
	Font font; // Global font for main menu text
	RenderWindow* m_window; // DONT DELETE

	set<pair<int, Drawable*>, CustomCompare> drawStack; // a set with the order in which graphics render

};

