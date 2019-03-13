#pragma once
#include "../../Header Files/Windows/BootMenu.h"


BootMenu::BootMenu(RenderWindow &window):GameMenu(window)
{
}


BootMenu::~BootMenu()
{
	delete backgroundMusic;
	delete title;
	drawStack.clear();
}

void BootMenu::init()
{
	opacity = 0;
	title = new Sprite(TextureHolder::GetTexture("./graphics/kgs.png"));// load emblem
	backgroundMusic = new Music();
	backgroundMusic->openFromFile("./music/MainMenu/KGS Intro.ogg"); // Load intro music
	backgroundMusic->play(); // start playing intro music
	backgroundMusic->setVolume((float)Controller::getMusicVolume()); // set volume of music
	drawStack[0] = title;
	vector<Vector2f> dimensions;
	dimensions.push_back(Vector2f(title->getLocalBounds().width, title->getLocalBounds().height));
	title->setPosition(Theme::renderRegion(Theme::Background, dimensions)[0]);
	// set emblem in the center
	Controller::setInitialized(true);
	Controller::setRunning(true);
}

void BootMenu::update(float &dtasSeconds)
{
	if (!Controller::isRunning())
	{
		Controller::setState(Controller::IN_MENU);
		Controller::setInitialized(false);
		backgroundMusic->stop();
		return;
	}
	const float FADE_IN_SPEED = 0.5f;
	const float START_FADE_IN = 1.0f;
	const float START_FADE_OUT = 6.0f;
	if ((backgroundMusic->getPlayingOffset().asSeconds() < START_FADE_OUT)
		&& (backgroundMusic->getPlayingOffset().asSeconds() > START_FADE_IN) && opacity < 255)
	{
		opacity += FADE_IN_SPEED;
	}
	else if ((backgroundMusic->getPlayingOffset().asSeconds() > START_FADE_OUT) && opacity > 0)
	{
		opacity -= FADE_IN_SPEED;
	}

	if (backgroundMusic->getStatus() != Music::Playing)
	{
		Controller::setRunning(false);
	}
	title->setColor(Color(255, 255, 255, (unsigned int)opacity));
}

void BootMenu::draw()
{
	for (pair<int,Drawable*> dr : drawStack)
	m_window->draw(*dr.second);
}

void BootMenu::input()
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		Controller::setRunning(false);
		Theme::clear();
	}
}

void BootMenu::actions()
{
}
