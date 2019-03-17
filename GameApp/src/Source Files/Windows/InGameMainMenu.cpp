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
	drawStack.clear();
	tabOrder.clear();
	backButton.clear();
}

void InGameMainMenu::init()
{
	clearTextures();
	initLayer(); // Initialize everything. Fresh start
	optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	totalTimePassed = 0;
}

void InGameMainMenu::update(float &dtasSeconds)
{
	if (!Controller::isExecuteSecondary(Controller::IN_GAME_MAIN_MENU))
	{
		Controller::setSecondaryInitialized(Controller::IN_GAME_MAIN_MENU, false);
		Theme::clearRegion(Theme::NewWindow);
		return;
	}
	totalTimePassed += dtasSeconds;
	if (guiElements.size() != 0) // TODO: maybe include an event (onChangeState)
	{
		checkGuiChangeState();
	}
}

void InGameMainMenu::actions()
{
	if (optionSelected == tabOrder.size() - 1) {
		if (depth != 1) {
			depth -= 1;
			initLayer();
			return;
		}
	}

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

void InGameMainMenu::initLayer()
{
	clearTextures();
	loadMenu = false;
	Theme::clearRegion(Theme::NewWindow);
	
	if (depth == 1) {
		loadTextGraphics(mainMenu);
		setBackgroundSprites(backgroundSpritesPath);
		initMenu();
	}
	else if (optionSelected == 0 && depth == 2) {
		Controller::setExecuteSecondary(Controller::IN_GAME_MAIN_MENU, false);
	}
	else if (optionSelected == 1 && depth == 2) {
		loadSaveFiles();
		loadMenu = true;
	}
	else if (optionSelected == 2 && depth == 2) {
		initOptions(Theme::NewWindow, 1);
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
	backgroundFillColor = new RectangleShape(Vector2f(WIN_WIDTH - 5, WIN_HEIGHT - 5));
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
	guiElements.clear();
	delete backgroundFillColor;
}

void InGameMainMenu::initOptions(Theme::Regions region, int pos)
{

	ValueBar* buffer = new ValueBar(m_window, Text("Music Volume", font, 30), font, region, (float)Controller::getMusicVolume());
	guiElements.push_back(buffer);
	drawStack[2 + drawStack.size()] = buffer;
	tabOrder[tabOrder.size()] = make_pair("GUI", buffer);

	vector<pair<string, string>> resolutions;
	for (Vector2i &res : Controller::getAvailableResolutions())
	{
		resolutions.push_back(make_pair(to_string(res.x), to_string(res.y)));
	}
	OptionBox* opBuffer = new OptionBox(m_window, Text("Resolution", font, 30), font, region, Controller::getResolutionID(), resolutions);
	guiElements.push_back(opBuffer);
	drawStack[2 + drawStack.size()] = opBuffer;
	tabOrder[tabOrder.size()] = make_pair("GUI", opBuffer);


	backgroundFillColor = new RectangleShape(Vector2f(700.f, 200.f));
	vector<Vector2f> dimensions;
	const Color background = Color(121, 132, 202);
	dimensions.push_back(backgroundFillColor->getSize());
	backgroundFillColor->setFillColor(background);
	drawStack[0] = backgroundFillColor;

	for (GuiElement * ge : guiElements) {
		dimensions.push_back(ge->getDimensions());
	}
	backButton[0] = "Back";
	loadTextGraphics(backButton);
	
	dimensions.push_back(Vector2f(menuTexts[0]->getLocalBounds().width, menuTexts[0]->getLocalBounds().height));
	vector<Vector2f> newPositions = Theme::renderRegion(region, dimensions, pos);
	Vector2f camOffset = Controller::getCameraOffset();

	backgroundFillColor->setPosition(Vector2f(newPositions[0].x +camOffset.x , newPositions[0].y + camOffset.y));

	for (unsigned int i = 0; i < guiElements.size(); i++) {
		guiElements[i]->setPosition(newPositions[i + 1],camOffset);
	}
	menuTexts[0]->setPosition(newPositions[newPositions.size() - 1] + camOffset);

	optionSelected = 0;
	guiElements[0]->setSelected();

}

void InGameMainMenu::initMenu()
{
	vector<Vector2f> dimensions; // vector with dimensions of elements
	dimensions.push_back(Vector2f(backgroundFillColor->getLocalBounds().width, backgroundFillColor->getLocalBounds().height));
	for (unsigned int i = 0; i < menuTexts.size(); i++) {
		dimensions.push_back(Vector2f(menuTexts[i]->getLocalBounds().width, menuTexts[i]->getLocalBounds().height));
	}
	// Render Window region
	vector<Vector2f> newPositions = Theme::renderRegion(Theme::NewWindow, dimensions, 1);
	Vector2f camOffset = Controller::getCameraOffset();

	for (unsigned int i = 0; i < newPositions.size(); i++) {
		newPositions[i] = Vector2f(newPositions[i].x + camOffset.x, newPositions[i].y + camOffset.y);
	}

	// set position of background
	backgroundFillColor->setPosition(Vector2f(newPositions[0].x, newPositions[0].y));
	backgroundSprites[0]->setPosition(Vector2f(newPositions[0].x, newPositions[0].y));
	// set positioon of elements of menu
	for (unsigned int i = 0; i < menuTexts.size(); i++) {
		newPositions[i + 1] = Vector2f(newPositions[i + 1].x, newPositions[i + 1].y - dimensions[i + 1].y / 2.f);
		menuTexts[i]->setPosition(newPositions[i + 1]);
	}
}

