#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Core/textureHolder.h"
#include "fstream"
#include "GameMenu.h"
#include "Theme/Background.h"

class BootMenu:public GameMenu 
{
public:
	BootMenu(RenderWindow &window);
	~BootMenu();

	void init() override;
	void draw() override;
	void update(float&) override;
	void actions() override;
	void input() override;

private:
	// necessary globals
	Music *backgroundMusic; // Background music for menu
	Sprite *title; // used for emblem and game title
	float opacity; // nedded for fade in animation
	// ---------------
};

