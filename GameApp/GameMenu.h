#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "textureHolder.h"
#include "fstream"
#include "Controller.h"

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

	float MUSIC_VOLUME = (float) Controller::getMusicVolume();

};

