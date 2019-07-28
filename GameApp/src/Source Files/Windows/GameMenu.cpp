#pragma once
#include "../../Header Files/Windows/GameMenu.h"


GameMenu::GameMenu(RenderWindow &window)
{
	m_window = &window;
	font.loadFromFile("./graphics/fonts/ARCADECLASSIC.TTF");
}


GameMenu::~GameMenu()
{
}

void GameMenu::mouseInput(Vector2i) 
{

}