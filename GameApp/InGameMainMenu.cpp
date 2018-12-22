#include "pch.h"
#include "InGameMainMenu.h"


InGameMainMenu::InGameMainMenu(RenderWindow &window) :GameMenu(window)
{
	index = 0;
	depth = 1;
}


InGameMainMenu::~InGameMainMenu()
{
	menuTexts.clear();
	menuSprites.clear();
	backgroundSprites.clear();
}

void InGameMainMenu::init()
{
	initData(); // Initialize everything. Fresh start
	optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	totalTimePassed = 0;
}

void InGameMainMenu::draw()
{
	m_window->draw(backgroundFillColor);
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

void InGameMainMenu::update(float dtasSeconds)
{
	if (!Controller::isExecuteSecondary(Controller::IN_GAME_MAIN_MENU))
	{
		Controller::setSecondaryInitialized(Controller::IN_GAME_MAIN_MENU, false);
		return;
	}

	totalTimePassed += dtasSeconds;
}

void InGameMainMenu::actions()
{
	if (index == 1 && depth == 2)
	{
		Controller::setExecuteSecondary(Controller::IN_GAME_MAIN_MENU, false);
		Controller::setLoadFile(true);
		Controller::setSaveFileDirectory(loadFilePath[optionSelected]);
	}
	else
	{
		switch (optionSelected)
		{
		case 0: // New Game
			//Loads intro cutscene or whatever
			Controller::setLoadFile(false);
			Controller::setExecuteSecondary(Controller::IN_GAME_MAIN_MENU, false);
			break;
		case 1: //Load Game
			index = 1;
			depth = 2;
			loadSaveFiles();
			break;
		case 2: //Options
			break;
		case 3: //Credits
			break;
		}
	}
}

void InGameMainMenu::input()
{
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		changeSeletedOption(-1);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	{
		changeSeletedOption(1);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		actions();
	}
}

void InGameMainMenu::initData()
{
	initMenuEnrties(mainMenu);
	setBackgroundSprites(backgroundSpritesPath);
}

void InGameMainMenu::initMenuEnrties(vector<string> menuEntries)
{
	const float CAMERA_POSITION_X = m_window->getView().getCenter().x - m_window->getSize().x / 2;
	const float CAMERA_POSITION_Y = m_window->getView().getCenter().y - m_window->getSize().y / 2;
	const int TEXT_HEIGHT = 15;
	const unsigned int NUMBER_OF_ENTRIES = menuEntries.size();
	const int WIN_HEIGHT = 256;
	const int WIN_WIDTH = 256;
	const float X_START_POS = CAMERA_POSITION_X; // used for offsetting everything in the x axis without too much effort
	const float Y_START_POS = CAMERA_POSITION_Y + m_window->getSize().y - WIN_HEIGHT; // used for offsetting everything in the y axis without too much effort
	const float MARGIN_LOGO = 0; // top and down margin of logo
	const float MARGINS = WIN_HEIGHT * 0.15f; // bottom and top margins of container
	const float HEIGHT_LOGO = 0; // to be initialized properly
	const float HEIGHT_CONTAINER = WIN_HEIGHT - 2 * MARGIN_LOGO - 2 * MARGINS - HEIGHT_LOGO;
	const float TOP_CONTAINER = 2 * MARGIN_LOGO + HEIGHT_LOGO;
	const float MARGIN_BETWEEN_ENTRIES = (float)((HEIGHT_CONTAINER - (TEXT_HEIGHT * NUMBER_OF_ENTRIES)) / (NUMBER_OF_ENTRIES-1));

	/*
		Adds Sprites to vector and trims them
		Sets Origin of sprites to center
		Set Position of Sprites
	*/
	menuTexts.clear();
	for (unsigned int i = 0; i < NUMBER_OF_ENTRIES; i++) {
		menuTexts.push_back(Text(menuEntries[i], font, 26));
		menuTexts[i].setFillColor(Color::White);
		FloatRect textRect = menuTexts[i].getLocalBounds();
		menuTexts[i].setOrigin(Vector2f(0,0));
		menuTexts[i].setPosition(sf::Vector2f((float)(X_START_POS + (WIN_WIDTH - textRect.width)/2),
			(float)Y_START_POS + MARGINS - textRect.height + TOP_CONTAINER + (textRect.height + MARGIN_BETWEEN_ENTRIES) * i));
	}
	
	optionSelected = 0;
	menuTexts[0].setFillColor(Color::Red); //set as default selected
}

void InGameMainMenu::loadSaveFiles()
{
}

void InGameMainMenu::changeSeletedOption(int direction)
{
	if (menuTexts.size() != 0)
	{
		menuTexts[optionSelected].setFillColor(Color::White);
		optionSelected += (menuTexts.size() + direction);
		optionSelected = optionSelected % menuTexts.size();
		menuTexts[optionSelected].setFillColor(Color::Red);
	}
}

void InGameMainMenu::setBackgroundSprites(vector<string> backgroundSpritesPath)
{
	const float CAMERA_POSITION_X = m_window->getView().getCenter().x - m_window->getSize().x / 2;
	const float CAMERA_POSITION_Y = m_window->getView().getCenter().y - m_window->getSize().y / 2;
	const unsigned int NUMBER_OF_SPRITES = backgroundSpritesPath.size();
	const int WIN_HEIGHT = 256;
	const int WIN_WIDTH = 256;
	const float X_START_POS = CAMERA_POSITION_X;									// used for offsetting everything in the x axis without too much effort
	const float Y_START_POS = CAMERA_POSITION_Y + m_window->getSize().y - WIN_HEIGHT; // used for offsetting everything in the y axis without too much effort
	const Color background = Color(121,132,202);


	backgroundSprites.clear();

	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++)
	{
		backgroundSprites.push_back(Sprite(TextureHolder::GetTexture(backgroundSpritesPath[i])));
		backgroundSprites[i].setPosition(Vector2f((float)X_START_POS,(float)Y_START_POS));
	}

	backgroundFillColor.setFillColor(background);
	backgroundFillColor.setPosition(Vector2f((float)X_START_POS, (float)Y_START_POS));
	backgroundFillColor.setSize(Vector2f(WIN_HEIGHT, WIN_WIDTH));
}

