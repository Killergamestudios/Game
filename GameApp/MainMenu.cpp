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
	menuTexts.clear();
	menuSprites.clear();
	backgroundSprites.clear();
}

void MainMenu::init() 
{
	initData(); // Initialize everything. Fresh start
	Controller::setInitialized(true);

	optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	totalTimePassed = 0;
	backgroundMusic->openFromFile("./music/MainMenu/Orchestral_Action_-_Last_Stand.ogg");
	backgroundMusic->play();
	backgroundMusic->setVolume(100.0f);
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

	for (unsigned int i = 0; i < guiElements.size(); i++)
	{
		m_window->draw(*guiElements[i]);
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

	totalTimePassed += dtasSeconds;
	animate(totalTimePassed, optionSelected);
	backgroundMusic->setVolume(Controller::getMusicVolume());
	
	if (guiElements.size() != 0) // TODO: maybe include an event (onChangeState)
	{
		for (unsigned int i = 0; i < guiElements.size(); i++) 
		{
			if (guiElements[i]->label.getString() == "Music Volume")
			{	
				Controller::setMusicVolume((int)guiElements[i]->getValue());
			}
		}
	}
}

void MainMenu::actions()
{
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
			clearTextures();
			Theme::clearRegion(Theme::MAINMENU);
			loadSaveFiles();
			break;
		case 2: //Options
			index = 2;
			depth = 2;
			clearTextures();
			initOptions();
			break;
		case 3: //Credits
			break;
		}
	}

	if (optionSelected == buttonsCounter - 1) {
		if (depth == 1) {
			m_window->close();
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
	else if (guiElements.size()!=0 && (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))) 
	{
		guiElements[optionSelected]->update(1);
	}
	else if (guiElements.size() != 0 && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)))
	{
		guiElements[optionSelected]->update(-1);
	}
}

void MainMenu::initData()
{
	backgroundMusic = new Music();
	initFileNamesToLoad(mainMenu);
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
	const float HEIGHT_CONTAINER = WIN_HEIGHT - 2 * MARGIN_LOGO - BOTTOM_MARGIN - HEIGHT_LOGO;
	const float MARGIN_BETWEEN_BUTTONS = (float)((HEIGHT_CONTAINER - (SPRITE_HEIGHT * NUMBER_OF_SPRITES)) / (NUMBER_OF_SPRITES-1));

	/*
		Adds Sprites to vector and trims them
		Sets Origin of sprites to center
		Set Position of Sprites 
	*/
	vector<FloatRect> dimensions; // vector with dimensions of elements

	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++)
	{
		menuSprites.push_back(Sprite(TextureHolder::GetTexture(fileNamesToLoad[i]), IntRect(0, 0, 256, 128)));
		dimensions.push_back(menuSprites[i].getLocalBounds());  // populate vector
	//	menuSprites[i].setOrigin(SPRITE_WIDTH / 2, SPRITE_HEIGHT / 2);  
	//	menuSprites[i].setPosition(Vector2f((float)((WIN_WIDTH / 2)),	
	//		(float)((TOP_CONTAINER + ((1 + 2 * i) * SPRITE_HEIGHT / 2) + MARGIN_BETWEEN_BUTTONS * (i + 1)))));
		drawStack.insert(make_pair(i,&menuSprites[i]));
	}
	vector<Vector2f> newPositions = Theme::renderRegion(Theme::MAINMENU, dimensions); // render elements in region. FloatRect is used as a wrapper
	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++) {
		menuSprites[i].setPosition(newPositions[i]);
	}
	menuSprites[0].setTextureRect(IntRect(256, 0, 256, 128)); // set NewGame as Default Selected
}


void MainMenu::loadTextGraphics(vector<string> textsArray)
{
	const float TEXT_LEFT_MARGIN = (float)(WIN_WIDTH / 10);
	const int MARGIN_BETWEEN_TEXT = 10;

	vector<FloatRect> dimensions; // vector with dimensions of elements
	for (unsigned int i = 0; i < textsArray.size(); i++) {
		menuTexts.push_back(Text(textsArray[i],font,24));
		dimensions.push_back(menuTexts[i].getLocalBounds());
		drawStack.insert(make_pair(2,&menuTexts[i]));
		menuTexts[i].setFillColor(Color::White);
	} 
	vector<Vector2f> newPositions = Theme::renderRegion(Theme::MAINMENU, dimensions);
	for (unsigned int i = 0; i < menuTexts.size(); i++) {
		menuTexts[i].setPosition(newPositions[i]);
	}
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

void MainMenu::changeSeletedOption(int direction) 
{	
	unsigned int oldOptionSelected = optionSelected;
	buttonsCounter = menuSprites.size() + menuTexts.size() + guiElements.size();
	optionSelected += (buttonsCounter + direction);
	optionSelected = optionSelected % buttonsCounter;

	if (menuSprites.size() != 0)
	{
		menuSprites[oldOptionSelected].setTextureRect(IntRect(0, 0, 256, 128));
		menuSprites[optionSelected].setTextureRect(IntRect(256, 0, 256, 128));
	}

	if (menuTexts.size() != 0)
	{
		menuTexts[oldOptionSelected].setFillColor(Color::White);
		menuTexts[optionSelected].setFillColor(Color::Red);
	}

	if (guiElements.size() != 0) 
	{
		guiElements[oldOptionSelected]->unSelect();
		guiElements[optionSelected]->setSelected();
	}
}

void MainMenu::clearTextures()
{
	menuTexts.clear();
	menuSprites.clear();
	optionSelected = 0;
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

void MainMenu::initOptions()
{
	const int WIN_HEIGHT = m_window->getSize().y;
	const int WIN_WIDTH = m_window->getSize().x;
	const float HEIGHT_LOGO = WIN_HEIGHT * 0.3f; // to be initialized properly
	const float MARGIN_LOGO = WIN_HEIGHT * 0.05f; // top and down margin of logo
	const float TOP_CONTAINER = 2 * MARGIN_LOGO + HEIGHT_LOGO;
	const float MARGIN_X = 0.05f*WIN_WIDTH;
	const float MARGIN_Y = 0.02f*WIN_HEIGHT;
	const float DISTANCE_BETWEEN = 30 + MARGIN_Y *2;
	
	guiElements.push_back(new ValueBar(m_window,Vector2f(MARGIN_X, TOP_CONTAINER),Text("Music Volume",font,30),font, Controller::getMusicVolume()));
	vector<pair<string, string>> resolutions; 
	for (Vector2i res : Controller::getAvailableResolutions()) 
	{
		resolutions.push_back(make_pair(to_string(res.x), to_string(res.y)));
	}
	guiElements.push_back(new OptionBox(m_window, Vector2f(MARGIN_X, TOP_CONTAINER + DISTANCE_BETWEEN), Text("Resolution", font, 30), font, Controller::getResolutionID(), resolutions));
	
	optionSelected = 0;
	guiElements[0]->setSelected();
}


