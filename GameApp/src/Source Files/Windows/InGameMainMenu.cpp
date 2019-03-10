#pragma once
#include "../../Header Files/Windows/InGameMainMenu.h"


InGameMainMenu::InGameMainMenu(RenderWindow &window) :MainMenu(window)
{
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
	clearTextures();
	initLayer(); // Initialize everything. Fresh start
	optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	totalTimePassed = 0;

	vector<Vector2f> dimensions; // vector with dimensions of elements
	dimensions.push_back(Vector2f(backgroundFillColor->getLocalBounds().width, backgroundFillColor->getLocalBounds().height));
	for (unsigned int i = 0; i < menuTexts.size(); i++) {
		dimensions.push_back(Vector2f(menuTexts[i]->getLocalBounds().width, menuTexts[i]->getLocalBounds().height));
	}
	vector<Vector2f> newPositions = Theme::renderRegion(Theme::NewWindow, dimensions, 1);
	Vector2f camOffset =Vector2f(m_window->getView().getCenter().x - m_window->getView().getSize().x / 2.f, 
								m_window->getView().getCenter().y - m_window->getView().getSize().y / 2.f);
	backgroundFillColor->setPosition(Vector2f(newPositions[0].x + camOffset.x, newPositions[0].y + camOffset.y));
	backgroundSprites[0]->setPosition(Vector2f(newPositions[0].x + camOffset.x, newPositions[0].y + camOffset.y));
	for (unsigned int i = 0; i < menuTexts.size(); i++) {
		
		newPositions[i + 1] = Vector2f(newPositions[i + 1].x + camOffset.x, newPositions[i + 1].y - dimensions[i + 1].y / 2.f + camOffset.y);
		menuTexts[i]->setPosition( newPositions[i + 1]);
	}
}

void InGameMainMenu::draw()
{
	for (pair<int, Drawable*> dr : drawStack)
		m_window->draw(*dr.second);
}

void InGameMainMenu::update(float dtasSeconds)
{
	if (!Controller::isExecuteSecondary(Controller::IN_GAME_MAIN_MENU))
	{
		Controller::setSecondaryInitialized(Controller::IN_GAME_MAIN_MENU, false);
		Theme::clearRegion(Theme::NewWindow);
		return;
	}

	totalTimePassed += dtasSeconds;
}

void InGameMainMenu::actions()
{
	if (loadMenu)
	{
		Controller::setExecuteSecondary(Controller::IN_GAME_MAIN_MENU, false);
		Controller::setLoadFile(true);
		Controller::setSaveFileDirectory(loadFilePath[optionSelected]);
	} 
	else if (depth == 1)
	{
		depth++;
		initLayer();
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

void InGameMainMenu::initLayer()
{
	clearTextures();
	loadMenu = false;
	Theme::clearRegion(Theme::MainMenu);
	//backButton[0] = "Back";

	if (depth == 1) {
		loadTextGraphics(mainMenu);
		setBackgroundSprites(backgroundSpritesPath);
	}
	else if (optionSelected == 0 && depth == 2) {
		Controller::setExecuteSecondary(Controller::IN_GAME_MAIN_MENU, false);
		Theme::clearRegion(Theme::NewWindow);
	}
	else if (optionSelected == 1 && depth == 2) {
		loadSaveFiles();
		loadMenu = true;

	}
	else if (optionSelected == 2 && depth == 2) {
		//initOptions();
	}
	else if (optionSelected == 3 && depth == 2) {
		Controller::setExecuteSecondary(Controller::IN_GAME_MAIN_MENU, false);
		Controller::setState(Controller::IN_MENU);
		Controller::setRunning(false);
		Controller::setInitialized(false);
	}

	optionSelected = 0;
}

void InGameMainMenu::loadTextGraphics(vector<string> menuEntries)
{
	/*
		Adds Sprites to vector and trims them
		Sets Origin of sprites to center
		Set Position of Sprites
	*/
	for (unsigned int i = 0; i < menuEntries.size(); i++) {
		Text* buffer = new Text(menuEntries[i], font, 24);
		menuTexts.push_back(buffer);
		drawStack[drawStack.size() + 2] = buffer;
		tabOrder[tabOrder.size()] = make_pair("TXT", buffer);
		buffer->setFillColor(Color::White);
	}

	if (tabOrder.size() == menuTexts.size())
		menuTexts[0]->setFillColor(Color::Red); //set as default selected
}

void InGameMainMenu::loadSaveFiles()
{
}

void InGameMainMenu::changeSeletedOption(int direction)
{
	// Disgusting but it works...
	if (tabOrder[optionSelected].first == "TXT") {
		((Text*)tabOrder[optionSelected].second)->setFillColor(Color::White);
	}
	else if (tabOrder[optionSelected].first == "SP") {
		((Sprite*)tabOrder[optionSelected].second)->setTextureRect(IntRect(0, 0, 256, 128));
	}
	optionSelected += (tabOrder.size() + direction);
	optionSelected = optionSelected % tabOrder.size();

	if (tabOrder[optionSelected].first == "TXT") {
		((Text*)tabOrder[optionSelected].second)->setFillColor(Color::Red);
	}
	else if (tabOrder[optionSelected].first == "SP") {
		((Sprite*)tabOrder[optionSelected].second)->setTextureRect(IntRect(256, 0, 256, 128));
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

	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++)
	{
		Sprite* buffer = new Sprite(TextureHolder::GetTexture(backgroundSpritesPath[i]));
		backgroundSprites.push_back(buffer);
		drawStack[1] = buffer;
		//backgroundSprites[i].setPosition(Vector2f((float)X_START_POS,(float)Y_START_POS));
	}
	backgroundFillColor = new RectangleShape(Vector2f(WIN_HEIGHT, WIN_WIDTH));
	backgroundFillColor->setFillColor(background);
	//backgroundFillColor.setPosition(Vector2f((float)X_START_POS, (float)Y_START_POS));
	drawStack[0] = backgroundFillColor;
}

void InGameMainMenu::clearTextures()
{
	menuTexts.clear();
	menuSprites.clear();
	drawStack.clear();
	tabOrder.clear();
	backgroundSprites.clear();
}

