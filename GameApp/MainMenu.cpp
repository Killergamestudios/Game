#include "pch.h"
#include "MainMenu.h"
#include "fstream"
#include <iostream>
using namespace std;

MainMenu::MainMenu(RenderWindow &window, map<string, string> &controlUnit)
{
	m_window = &window;
	returnState = &controlUnit;
	index = 0;
	depth = 1;
	font.loadFromFile("./graphics/fonts/ARCADECLASSIC.TTF");
}


MainMenu::~MainMenu()
{
}

// -------------------------------
// Begin of Boot related functions
// -------------------------------

void MainMenu::initBoot()
{
	opacity = 0;
	title = new Sprite(TextureHolder::GetTexture("./graphics/kgs.png"));// load emblem
	backgroundMusic = new Music();
	backgroundMusic->openFromFile("./music/MainMenu/KGS Intro.ogg"); // Load intro music
	backgroundMusic->play(); // start playing intro music
	title->setPosition(Vector2f((float)(m_window->getSize().x - title->getTexture()->getSize().x) / 2,
		(float)(m_window->getSize().y - title->getTexture()->getSize().y) / 2));
	(*returnState)["Initialized"] = "true";
	(*returnState)["Running"] = "true";
	// set emblem in center 
}

void MainMenu::updateBoot()
{
	if ((*returnState)["Running"] == "false")
	{
		(*returnState)["Next State"] = "InMenu";
		(*returnState)["Initialized"] = "";
		backgroundMusic->stop();
		return;
	}
	const float FADE_IN_SPEED = 0.5f;
	const float START_FADE_IN = 1.0f;
	const float START_FADE_OUT = 6.0f;
	if ((backgroundMusic->getPlayingOffset().asSeconds() < START_FADE_OUT)
		&& (backgroundMusic->getPlayingOffset().asSeconds() > START_FADE_IN) && opacity < 255)
	{
		opacity += FADE_IN_SPEED;
	}
	else if ((backgroundMusic->getPlayingOffset().asSeconds() > START_FADE_OUT) && opacity > 0)
	{
		opacity -= FADE_IN_SPEED;
	}

	if (backgroundMusic->getStatus() != Music::Playing)
	{
		(*returnState)["Running"] = "false";
	}
	title->setColor(Color(255, 255, 255, (unsigned int)opacity));
}

void MainMenu::drawBoot()
{
	m_window->draw(*title);
}

// -----------------------------
// End of Boot related functions
// -----------------------------

// -----------------------------------
// Begin of MainMenu related functions
// -----------------------------------
void MainMenu::initMenu()
{
	init(); // Initialize everything. Fresh start
	(*returnState)["Initialized"] = "true";

	optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	totalTimePassed = 0;
	backgroundMusic->openFromFile("./music/MainMenu/Orchestral_Action_-_Last_Stand.ogg");
	backgroundMusic->play();
	backgroundMusic->setVolume(0.0f);
	backgroundMusic->setLoop(true);
	(*returnState)["Running"] = "true";
}

void MainMenu::init()
{
	clearData();
	backgroundMusic = new Music();
	initFileNamesToLoad(mainMenu);
}

void MainMenu::clearData()
{
	returnState->clear(); // Clears map because a new State is invoked
	if(backgroundMusic == NULL) delete backgroundMusic;
	backgroundMusic = NULL;
	if (title == NULL) delete title;
	title = NULL;
}

void MainMenu::clearTextures()
{
	menuTexts.clear();
	menuSprites.clear();
}

void MainMenu::initFileNamesToLoad(vector<string> fileNames)
{
	fileNamesToLoad.clear();
	for (int i = 0; i < fileNames.size(); i++) {
		fileNamesToLoad.push_back(fileNames[i]);
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
	menuSprites.clear();
	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++)
	{
		menuSprites.push_back(Sprite(TextureHolder::GetTexture(fileNamesToLoad[i]), IntRect(0, 0, 256, 128))); 
		menuSprites[i].setOrigin(SPRITE_WIDTH / 2, SPRITE_HEIGHT / 2);  
		menuSprites[i].setPosition(Vector2f((float)WIN_WIDTH / 2,	
			(float)TOP_CONTAINER + ((1 + 2 * i) * SPRITE_HEIGHT / 2) + MARGIN_BETWEEN_BUTTONS * (i + 1)));
	}

	menuSprites[0].setTextureRect(IntRect(256, 0, 256, 128)); // set NewGame as Default Selected
}


void MainMenu::loadTextGraphics(vector<string> textsArray)
{
	const int WIN_HEIGHT = m_window->getSize().y;
	const int WIN_WIDTH = m_window->getSize().x;
	const int HEIGHT_LOGO = WIN_HEIGHT * 0.3f; // to be initialized properly
	const int MARGIN_LOGO = WIN_HEIGHT * 0.05f; // top and down margin of logo
	const int TOP_CONTAINER = 2 * MARGIN_LOGO + HEIGHT_LOGO;
	const int TEXT_LEFT_MARGIN = WIN_WIDTH / 10;
	const int MARGIN_BETWEEN_TEXT = 10;

	menuTexts.clear();
	for (int i = 0; i < textsArray.size(); i++) {
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

void MainMenu::updateMenu(float dtasSeconds)
{
	if ((*returnState)["Running"] == "false")
	{
		(*returnState)["Next State"] = "Loading";
		(*returnState)["Initialized"] = "";
		backgroundMusic->stop();
		return;
	}

	fadeInMusic(*backgroundMusic);
	totalTimePassed += dtasSeconds;
	animate(totalTimePassed, optionSelected);
	drawMenu();
}

void MainMenu::drawMenu() {
	for (unsigned int i = 0; i < menuSprites.size(); i++)
	{
		m_window->draw(menuSprites[i]);
	}

	for (unsigned int i = 0; i < menuTexts.size(); i++)
	{
		m_window->draw(menuTexts[i]);
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

void MainMenu::actions()
{	
	clearTextures();
	if (index == 1 && depth == 2) 
	{
		//(*returnState)["Running"] = "false";
		//(*returnState)["Initialized"] = "";
		//(*returnState)["Next State"] = "Loading";
		//(*returnState)["Load Game"] = "true";
		//(*returnState)["Save File"] = "..."; // TODO: fix load;
		// TODO: load from selected file
	} 
	else
	{
		switch (optionSelected)
		{
		case 0: // New Game
			//Loads intro cutscene or whatever
			(*returnState)["Running"] = "false";
			(*returnState)["Initialized"] = "";
			(*returnState)["Next State"] = "Loading";
			(*returnState)["Load Game"] = "false";
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

void MainMenu::loadSaveFiles() {
	string lineReader;
	const string saveFileMapDirectory = "./savefiles/saveFilesMap.txt";
	vector<string> saveFilesArray;

	saveFile.open(saveFileMapDirectory);
	
	while (getline(saveFile, lineReader)) {
		saveFilesArray.push_back(lineReader);
	}

	loadTextGraphics(saveFilesArray);

}

// ---------------------------------
// End of MainMenu related functions
// ---------------------------------


