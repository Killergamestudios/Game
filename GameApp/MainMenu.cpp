#include "pch.h"
#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(RenderWindow &window)
{
	m_window = &window;
	m_state = MainMenuState::opening;
	if (!font.loadFromFile("./graphics/fonts/ARCADECLASSIC.ttf")) {}
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

	image.setPosition(Vector2f((float)(m_window->getSize().x - image.getTexture()->getSize().x )/2, 
							(float)(m_window->getSize().y - image.getTexture()->getSize().y)/2));
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
	m_state = MainMenuState::Main;
}

void MainMenu::setText()
{
	const int WIN_HEIGHT = m_window->getSize().y;
	const int WIN_WIDTH = m_window->getSize().x;
	const int MARGIN_LOGO = 100; // top and down margin of logo
	const int BOTTOM_MARGIN = 200; // bottom margin
	const int HEIGHT_LOGO = 300; // to be initialized properly
	const int HEIGHT_CONTAINER = WIN_HEIGHT - 2 * MARGIN_LOGO - BOTTOM_MARGIN - HEIGHT_LOGO;
	const float MARGIN_BETWEEN_TEXT = (float) HEIGHT_CONTAINER / texts.size();
	const int TOP_CONTAINER = 2 * MARGIN_LOGO + HEIGHT_LOGO;

	for (unsigned int i = 0; i < texts.size(); i++) 
	{
		textArray.push_back(Text(texts[i],font,40));
		sf::FloatRect textRect = textArray[i].getLocalBounds();
		textArray[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		textArray[i].setPosition(Vector2f((float)WIN_WIDTH / 2, (float)TOP_CONTAINER + MARGIN_BETWEEN_TEXT * (i + 1)));
	}
	textArray[0].setFillColor(Color::Cyan);
	textArray[0].setCharacterSize(50);
}

int MainMenu::menu()
{	
	texts.push_back("New Game");
	texts.push_back("Load Game");
	texts.push_back("Options");
	texts.push_back("Credits");
	setText();

	int indexFileToLoad = 0;
	int optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	bool keyPressed = false;
	while (true)
	{
		Event evt;
		while (m_window->pollEvent(evt))
		{
			if (evt.type == Event::KeyReleased) {
				keyPressed = false;
				break;
			}
		}
		if (!keyPressed)
		{
		//	cout << "1st " << keyPressed << endl;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				keyPressed = true;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
			{
				keyPressed = true;
				textArray[optionSelected].setFillColor(Color::White);
				textArray[optionSelected].setCharacterSize(40);
				optionSelected += 3;
				optionSelected = optionSelected % 4;
				textArray[optionSelected].setFillColor(Color::Cyan);
				textArray[optionSelected].setCharacterSize(50);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
			{
				keyPressed = true;
				textArray[optionSelected].setFillColor(Color::White);
				textArray[optionSelected].setCharacterSize(40);
				optionSelected += 5;
				optionSelected = optionSelected % 4;
				textArray[optionSelected].setFillColor(Color::Cyan);
				textArray[optionSelected].setCharacterSize(50);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				keyPressed = true;
				if (!actions(optionSelected, indexFileToLoad))
				{
					break;
				}
			}
		//	cout << "2st " << keyPressed << endl;
		}
		draw();
	}
	return indexFileToLoad;
}

void MainMenu::draw() {
	m_window->clear();
	for (unsigned int i = 0; i < textArray.size(); i++)
	{ 
		m_window->draw(textArray[i]);
	}
	m_window->display();
}

bool MainMenu::actions(int optionSelected, int &indexFileToLoad)
{
	switch (optionSelected)
	{
	case 0: // New Game
		//Loads intro cutscene or whatever
		indexFileToLoad = 0;
		return false;
		break;
	case 1: //Load Game
		return false;
		break;
	case 2: //Options
		return false;
		break;
	case 3: //Credits
		return false;
		break;
	}
	return true;
}



