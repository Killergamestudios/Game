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

void MainMenu::setMenuSprites()
{
	const int WIN_HEIGHT = m_window->getSize().y;
	const int WIN_WIDTH = m_window->getSize().x;
	const int MARGIN_LOGO = 50; // top and down margin of logo
	const int BOTTOM_MARGIN = 50; // bottom margin
	const int HEIGHT_LOGO = 200; // to be initialized properly
	const int HEIGHT_CONTAINER = WIN_HEIGHT - 2 * MARGIN_LOGO - BOTTOM_MARGIN - HEIGHT_LOGO;
	const int TOP_CONTAINER = 2 * MARGIN_LOGO + HEIGHT_LOGO;
	const int SPRITE_WIDTH = 256;
	const int SPRITE_HEIGHT = 128;
	const int NUMBER_OF_SPRITES = fileNamesToLoad.size();
	const float MARGIN_BETWEEN_BUTTONS = (float)((HEIGHT_CONTAINER - (SPRITE_HEIGHT * NUMBER_OF_SPRITES)) / NUMBER_OF_SPRITES);
	
	/*
		Adds Sprites to vector and trims them
		Sets Origin of sprites to center
		Set Position of Sprites 
	*/
	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++)
	{
		menuSprites.push_back(Sprite(TextureHolder::GetTexture(fileNamesToLoad[i]), IntRect(0, 0, 256, 128))); 
		menuSprites[i].setOrigin(SPRITE_WIDTH / 2, SPRITE_HEIGHT / 2);  
		menuSprites[i].setPosition(Vector2f((float)WIN_WIDTH / 2,	
			(float)TOP_CONTAINER + ((1 + 2 * i) * SPRITE_HEIGHT / 2) + MARGIN_BETWEEN_BUTTONS * (i + 1)));
	}

	menuSprites[0].setTextureRect(IntRect(256, 0, 256, 128)); // set NewGame as Default Selected
}


void MainMenu::animate(float &totaltimepassed, int optionSelected) {
	const float ANIMATION_SPEED = 0.3f;
	if (totaltimepassed > ANIMATION_SPEED) {
		totaltimepassed -= ANIMATION_SPEED;
		int left = menuSprites[optionSelected].getTextureRect().left; // get left position of previous selected texture
		left = left == 256 ? 512 : 256;
		menuSprites[optionSelected].setTextureRect(IntRect(left, 0, 256, 128));
	}

}

int MainMenu::menu()
{	
	for (string name: mainMenu) {
		fileNamesToLoad.push_back(name);
	} // populate array fileNameToLoad in order to load the sprites
	setMenuSprites();

	int indexFileToLoad = 0;
	int optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	bool keyPressed = false;
	Clock clock;//
	float totaltimepassed = 0;//
	while (true)
	{
		Time dt = clock.restart();//
		totaltimepassed += dt.asSeconds();//
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
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				keyPressed = true;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
			{
				menuSprites[optionSelected].setTextureRect(IntRect(0, 0, 256, 128));
				keyPressed = true;
				optionSelected += 3;
				optionSelected = optionSelected % 4;
				menuSprites[optionSelected].setTextureRect(IntRect(256, 0, 256, 128));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
			{
				menuSprites[optionSelected].setTextureRect(IntRect(0, 0, 256, 128));
				keyPressed = true;
				optionSelected += 5;
				optionSelected = optionSelected % 4;
				menuSprites[optionSelected].setTextureRect(IntRect(256, 0, 256, 128));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				keyPressed = true;
				if (!actions(optionSelected, indexFileToLoad))
				{
					break;
				}
			}
		}
		animate(totaltimepassed, optionSelected);
		draw();
	}
	return indexFileToLoad;
}

void MainMenu::draw() {
	m_window->clear();
	for (unsigned int i = 0; i < menuSprites.size(); i++)
	{ 
		m_window->draw(menuSprites[i]);
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



