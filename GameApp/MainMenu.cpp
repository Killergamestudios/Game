#include "pch.h"
#include "MainMenu.h"
#include <iostream>

using namespace std;

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
	const float FADE_IN_SPEED = 0.5f;
	const float START_FADE_IN = 1.0f;
	const float START_FADE_OUT = 6.0f;
	float opacity = 0;
	
	Sprite image(TextureHolder::GetTexture("./graphics/kgs.png"));// load emblem

	sf::Music music;
	music.openFromFile("./music/MainMenu/KGS Intro.ogg"); // Load intro music
	music.play(); // start playing intro music

	image.setPosition(Vector2f((float)(m_window->getSize().x - image.getTexture()->getSize().x )/2, 
							(float)(m_window->getSize().y - image.getTexture()->getSize().y)/2)); 
	// set emblem in center 

	while (openingPlaying) {

		// Fade in and fade out code
		if ((music.getPlayingOffset().asSeconds() < START_FADE_OUT)
			&& (music.getPlayingOffset().asSeconds() > START_FADE_IN) && opacity < 255)
		{
			opacity += FADE_IN_SPEED;
		}
		else if ((music.getPlayingOffset().asSeconds() > START_FADE_OUT) && opacity > 0)
		{
			opacity -= FADE_IN_SPEED;
		}

		// Stop while if key is Pressed or music stop playing
		if (Keyboard::isKeyPressed(Keyboard::Space) || music.getStatus() != Music::Playing)
			openingPlaying = false;
		
		//plays the opening
		image.setColor(Color(255, 255, 255, (unsigned int)opacity));
		m_window->clear();
		m_window->draw(image);
		m_window->display();
	}
	m_window->clear();
	m_window->display();
	m_state = MainMenuState::Main;
}

void MainMenu::init()
{
	initFileNamesToLoad(mainMenu);
	
}

template <size_t N>
void MainMenu::initFileNamesToLoad(const string (&fileNames)[N]) // pass array by reference
{
	fileNamesToLoad.clear();
	for (string name : fileNames) {
		fileNamesToLoad.push_back(name);
	} // populate array fileNameToLoad in order to load the sprites
	setMenuSprites();
}

void MainMenu::setMenuSprites()
{
	const int WIN_HEIGHT = m_window->getSize().y;
	const int WIN_WIDTH = m_window->getSize().x;
	const int MARGIN_LOGO = WIN_HEIGHT * 0.05f; // top and down margin of logo
	const int BOTTOM_MARGIN = WIN_HEIGHT * 0.05f; // bottom margin
	const int HEIGHT_LOGO = WIN_HEIGHT * 0.3f; // to be initialized properly
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

void MainMenu::fadeInMusic(Music & music)
{
	const float FADE_IN_SPEED = 0.01f;
	float currentVolume = music.getVolume();
	if (currentVolume < 100.0f) {
		music.setVolume(currentVolume + FADE_IN_SPEED);
	}
}

int MainMenu::menu()
{
	init(); // Initialize everything. Fresh start
	const float CHANGE_SELECTION_SPEED = 0.5f;
	int indexFileToLoad = 0;
	int optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	bool keyPressed = false;
	Clock clock;
	float totaltimepassed = 0; 
	float overwriteKeyPressed = 0; 
	sf::Music music;
	music.openFromFile("./music/MainMenu/Orchestral_Action_-_Last_Stand.ogg");
	music.play();
	music.setVolume(0.0f);
	music.setLoop(true);
	while (true)
	{
		fadeInMusic(music);
		Time dt = clock.restart();
		totaltimepassed += dt.asSeconds();
		overwriteKeyPressed += dt.asSeconds();
		Event evt;
		while (m_window->pollEvent(evt))
		{
			if (evt.type == Event::KeyReleased) {
				keyPressed = false;
				break;
			}
		}
		if (!keyPressed || overwriteKeyPressed > CHANGE_SELECTION_SPEED)
		{
			overwriteKeyPressed = 0;
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
	music.stop();
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



