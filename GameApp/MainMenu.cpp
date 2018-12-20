#include "pch.h"
#include "MainMenu.h"
#include "fstream"
#include <iostream>
using namespace std;

MainMenu::MainMenu(RenderWindow &window):GameMenu(window)
{
	index = 0;
	depth = 1;
}


MainMenu::~MainMenu()
{
	if (backgroundMusic == NULL) delete backgroundMusic;
	backgroundMusic = NULL;
	if (title == NULL) delete title;
	title = NULL;
}

void MainMenu::init() 
{
	initData(); // Initialize everything. Fresh start
	Controller::setInitialized(true);

	optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	totalTimePassed = 0;
	backgroundMusic->openFromFile("./music/MainMenu/Orchestral_Action_-_Last_Stand.ogg");
	backgroundMusic->play();
	backgroundMusic->setVolume(0.0f);
	backgroundMusic->setLoop(true);

	Controller::setRunning(true);
}

void MainMenu::draw() 
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

void MainMenu::update(float dtasSeconds) {
	if (!Controller::isRunning())
	{
		Controller::setState(Controller::LOADING);
		Controller::setInitialized(false);
		backgroundMusic->stop();
		return;
	}

	fadeInMusic(*backgroundMusic);
	totalTimePassed += dtasSeconds;
	animate(totalTimePassed, optionSelected);
	draw();
}

void MainMenu::actions()
{
	clearTextures();
	if (index == 1 && depth == 2)
	{
		Controller::setRunning(false);
		Controller::setLoadFile(true);
		Controller::setSaveFileDirectory(loadFilePath[optionSelected]);
	}
	else
	{
		switch (optionSelected)
		{
		case 0: // New Game
			//Loads intro cutscene or whatever
			Controller::setRunning(false);
			Controller::setLoadFile(false);
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

void MainMenu::input() {
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

void MainMenu::initData()
{
	backgroundMusic = new Music();
	initFileNamesToLoad(mainMenu);
}

void MainMenu::clearTextures()
{
	menuTexts.clear();
	menuSprites.clear();
}

void MainMenu::initFileNamesToLoad(vector<string> fileNames)
{
	fileNamesToLoad.clear();
	for (unsigned int i = 0; i < fileNames.size(); i++) {
		fileNamesToLoad.push_back(fileNames[i]);
	} // populate array fileNameToLoad in order to load the sprites

	setMenuSprites();
}

void MainMenu::setMenuSprites()
{
	const int SPRITE_WIDTH = 256;
	const int SPRITE_HEIGHT = 128;
	const unsigned int NUMBER_OF_SPRITES = fileNamesToLoad.size();
	const int WIN_HEIGHT = m_window->getSize().y;
	const int WIN_WIDTH = m_window->getSize().x;
	const int X_START_POS = 0; // used for offsetting everything in the x axis without too much effort
	const int Y_START_POS = 0; // used for offsetting everything in the y axis without too much effort
	const float MARGIN_LOGO = WIN_HEIGHT * 0.05f; // top and down margin of logo
	const float BOTTOM_MARGIN = WIN_HEIGHT * 0.05f; // bottom margin
	const float HEIGHT_LOGO = WIN_HEIGHT * 0.3f; // to be initialized properly
	const float HEIGHT_CONTAINER = WIN_HEIGHT - 2 * MARGIN_LOGO - BOTTOM_MARGIN - HEIGHT_LOGO;
	const float TOP_CONTAINER = 2 * MARGIN_LOGO + HEIGHT_LOGO;
	const float MARGIN_BETWEEN_BUTTONS = (float)((HEIGHT_CONTAINER - (SPRITE_HEIGHT * NUMBER_OF_SPRITES)) / NUMBER_OF_SPRITES);

	/*
		Adds Sprites to vector and trims them
		Sets Origin of sprites to center
		Set Position of Sprites 
	*/
	menuSprites.clear();
	backgroundSprites.clear();

	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++)
	{
		menuSprites.push_back(Sprite(TextureHolder::GetTexture(fileNamesToLoad[i]), IntRect(0, 0, 256, 128))); 
		menuSprites[i].setOrigin(SPRITE_WIDTH / 2, SPRITE_HEIGHT / 2);  
		menuSprites[i].setPosition(Vector2f((float)((WIN_WIDTH / 2) + X_START_POS),	
			(float)((TOP_CONTAINER + ((1 + 2 * i) * SPRITE_HEIGHT / 2) + MARGIN_BETWEEN_BUTTONS * (i + 1))) + Y_START_POS));
	}

	

	menuSprites[0].setTextureRect(IntRect(256, 0, 256, 128)); // set NewGame as Default Selected
}


void MainMenu::loadTextGraphics(vector<string> textsArray)
{
	const int WIN_HEIGHT = m_window->getSize().y;
	const int WIN_WIDTH = m_window->getSize().x;
	const float HEIGHT_LOGO = WIN_HEIGHT * 0.3f; // to be initialized properly
	const float MARGIN_LOGO = WIN_HEIGHT * 0.05f; // top and down margin of logo
	const float TOP_CONTAINER = 2 * MARGIN_LOGO + HEIGHT_LOGO;
	const float TEXT_LEFT_MARGIN = (float)(WIN_WIDTH / 10);
	const int MARGIN_BETWEEN_TEXT = 10;

	menuTexts.clear();
	for (unsigned int i = 0; i < textsArray.size(); i++) {
		menuTexts.push_back(Text(textsArray[i],font,24));
		menuTexts[i].setFillColor(Color::White);
		FloatRect textRect = menuTexts[i].getLocalBounds();
		menuTexts[i].setPosition(sf::Vector2f(TEXT_LEFT_MARGIN, 
			TOP_CONTAINER + (textRect.height + MARGIN_BETWEEN_TEXT) * i));
	} 
	optionSelected = 0;
	menuTexts[0].setFillColor(Color::Red); //set as default selected
}

void MainMenu::animate(float &totaltimepassed, int optionSelected) {
	const float ANIMATION_SPEED = 0.3f;
	if (menuSprites.size() != 0)
	{
		if (totaltimepassed > ANIMATION_SPEED) 
		{
			totaltimepassed -= ANIMATION_SPEED;
			int left = menuSprites[optionSelected].getTextureRect().left; // get left position of previous selected texture
			left = left == 256 ? 512 : 256;
			menuSprites[optionSelected].setTextureRect(IntRect(left, 0, 256, 128));
		}
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

void MainMenu::changeSeletedOption(int direction) {
	if (menuSprites.size() != 0)
	{
		menuSprites[optionSelected].setTextureRect(IntRect(0, 0, 256, 128));
		optionSelected += (menuSprites.size() + direction);
		optionSelected = optionSelected % menuSprites.size();
		menuSprites[optionSelected].setTextureRect(IntRect(256, 0, 256, 128));
	}

	if (menuTexts.size() != 0)
	{
		menuTexts[optionSelected].setFillColor(Color::White);
		optionSelected += (menuTexts.size() + direction);
		optionSelected = optionSelected % menuTexts.size();
		menuTexts[optionSelected].setFillColor(Color::Red);
	}
}

void MainMenu::loadSaveFiles() {
	string lineReader;
	const string saveFileMapDirectory = "./savefiles/saveFilesMap.txt";
	vector<string> saveFilesArray;

	saveFile.open(saveFileMapDirectory);
	
	while (getline(saveFile, lineReader)) {
		string nameOfSaveFile = lineReader.substr(0,lineReader.find("|"));
		saveFilesArray.push_back(nameOfSaveFile);
		string pathOfSaveFile = lineReader.substr(lineReader.find("|") + 1);
		loadFilePath.push_back(pathOfSaveFile);
	}

	loadTextGraphics(saveFilesArray);

}


