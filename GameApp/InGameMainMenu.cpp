#include "pch.h"
#include "InGameMainMenu.h"


InGameMainMenu::InGameMainMenu(RenderWindow &window) :GameMenu(window)
{
}


InGameMainMenu::~InGameMainMenu()
{
}

void InGameMainMenu::init()
{
	initData(); // Initialize everything. Fresh start
	optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	totalTimePassed = 0;
}

void InGameMainMenu::draw()
{
	for (unsigned int i = 0; i < backgroundSprites.size(); i++)
	{
		m_window->draw(backgroundSprites[i]);
	}

	for (unsigned int i = 0; i < menuSprites.size(); i++)
	{
		m_window->draw(menuSprites[i]);
	}

	for (unsigned int i = 0; i < menuTexts.size(); i++)
	{
		m_window->draw(menuTexts[i]);
	}
}

void InGameMainMenu::update(float)
{
}

void InGameMainMenu::actions()
{
}

void InGameMainMenu::input()
{
}

void InGameMainMenu::initData()
{
	initMenuEnrties(mainMenu);
}

void InGameMainMenu::clearTextures()
{
}

void InGameMainMenu::initMenuEnrties(vector<string> menuEntries)
{
}

void InGameMainMenu::setMenuSprites()
{
}

void InGameMainMenu::loadTextGraphics(vector<string> textsArray)
{
}

void InGameMainMenu::loadSaveFiles()
{
}

void InGameMainMenu::changeSeletedOption(int direction)
{
}

