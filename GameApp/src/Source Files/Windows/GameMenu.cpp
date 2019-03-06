#include "pch.h"
#include "GameMenu.h"


GameMenu::GameMenu(RenderWindow &window)
{
	m_window = &window;
	font.loadFromFile("./graphics/fonts/ARCADECLASSIC.TTF");
}


GameMenu::~GameMenu()
{
}
