#include "pch.h"
#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(RenderWindow &window)
{
	m_window = &window;
	m_state = MainMenuState::opening;
}


MainMenu::~MainMenu()
{
}

void MainMenu::boot()
{
	bool openingPlaying = true;
	//WIP- Start playing a video file here <-
	Clock clock;//
	float totaltimepassed = 0;//
	Sprite image(TextureHolder::GetTexture("./graphics/kgs.png"));//
	
	image.setPosition((m_window->getSize().x - image.getTexture()->getSize().x )/2,
					  (m_window->getSize().y - image.getTexture()->getSize().y)/2);
	Event event;
	while (openingPlaying) {
		//plays the opening
		m_window->clear();//
		m_window->draw(image);//
		m_window->display();//
		Time dt = clock.restart();//
		totaltimepassed += dt.asSeconds();//
		if (Keyboard::isKeyPressed(Keyboard::Space) || totaltimepassed > 10.0f  )
			openingPlaying = false;

	}
	m_window->clear();
	m_window->display();
}

