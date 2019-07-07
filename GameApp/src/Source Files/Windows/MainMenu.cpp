#pragma once
#include "../../Header Files/Windows/MainMenu.h"
#include "fstream"
#include <iostream>
using namespace std;

MainMenu::MainMenu(RenderWindow &window):GameMenu(window)
{
	depth = 1;
	loadMenu = false;
	backButton.push_back("Quit");
}


MainMenu::~MainMenu()
{
	if (backgroundMusic != NULL) delete backgroundMusic;
	backgroundMusic = NULL;
	if (title != NULL) delete title;
	title = NULL;
	menuTexts.clear();
	menuSprites.clear();
	backgroundSprites.clear();
	drawStack.clear();
	tabOrder.clear();
	backButton.clear();
}

void MainMenu::init() 
{
	tempLogo = new RectangleShape(Vector2f(m_window->getView().getSize().x, 0.25f*m_window->getView().getSize().y));
	tempLogo->setPosition((new Logo(false))->renderRegion(tempLogo->getSize()));
	initLayer(); // Initialize everything. Fresh start
	Controller::setInitialized(true);
	optionSelected = 0; // 0 for New Game , 1 for Load game ,2 for Options,  3 for Credits
	totalTimePassed = 0;
	backgroundMusic = new Music();
	backgroundMusic->openFromFile("./music/MainMenu/Orchestral_Action_-_Last_Stand.ogg");
	backgroundMusic->play();
	backgroundMusic->setVolume((float)Controller::getMusicVolume());
	backgroundMusic->setLoop(true);

	Controller::setRunning(true);
}

void MainMenu::draw() 
{
	for (pair<int ,Drawable*> dr :  drawStack)
		m_window->draw(*dr.second);
}

void MainMenu::update(float& dtasSeconds) {
	if (!Controller::isRunning())
	{
		Controller::setState(Controller::LOADING);
		Controller::setInitialized(false);
		backgroundMusic->stop();
		return;
	}

	totalTimePassed += dtasSeconds;
	animate();
	
	backgroundMusic->setVolume((float)Controller::getMusicVolume());
	if (guiElements.size() != 0) // TODO: maybe include an event (onChangeState)
	{
		checkGuiChangeState();
	}
}

void MainMenu::actions()
{
	if (optionSelected == tabOrder.size() - 1) {
		if (depth == 1) {
			Controller::quit();
		}
		else if (depth != 1) {
			depth -= 1;
			initLayer();
		}
		return;
	}

	if (loadMenu)
	{
		Controller::setRunning(false);
		Controller::setLoadFile(true);
		Controller::setSaveFileDirectory(loadFilePath[optionSelected]);
	}
	else if(depth == 1)
	{
		depth++;
		initLayer();
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
	else if (guiElements.size()!=0 && optionSelected < guiElements.size() && (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))) 
	{
		guiElements[optionSelected]->update(1);
	}
	else if (guiElements.size() != 0 && optionSelected < guiElements.size() && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)))
	{
		guiElements[optionSelected]->update(-1);
	}
}

void MainMenu::initLayer()
{
	clearTextures();
	loadMenu = false;

	if (depth == 1) {
		initFileNamesToLoad(mainMenu, new MainMenuWindow(true, false));
	}
	else if (optionSelected == 0 && depth == 2) {
		Controller::setRunning(false);
		Controller::setLoadFile(false);
	}
	else if (optionSelected == 1 && depth == 2) {
		loadSaveFiles();
		loadMenu = true;
		backButton.push_back("Back");
		loadTextGraphics(backButton, new BackButton(true, false));
	}
	else if (optionSelected == 2 && depth == 2) {
		initOptions(new MainMenuWindow(true, false));
		backButton.push_back("Back");
		loadTextGraphics(backButton, new BackButton(true, false));
	}
	else if (optionSelected == 3 && depth == 2) {
		backButton.push_back("Back");
		loadTextGraphics(backButton, new BackButton(true, false));
	}

	optionSelected = 0;
	totalTimePassed = 0;	
}

void MainMenu::clearTextures()
{
	menuTexts.clear();
	menuSprites.clear();
	drawStack.clear();
	tabOrder.clear();
	guiElements.clear();
	dimensions.clear();
	backButton.clear();
	loadFilePath.clear();
}

void MainMenu::checkGuiChangeState()
{
	for (unsigned int i = 0; i < guiElements.size(); i++)
	{
		if (guiElements[i]->label.getString() == "Music Volume")
		{
			Controller::setMusicVolume((int)guiElements[i]->getValue());
		} 
		else if (guiElements[i]->label.getString() == "Sound Volume")
		{
			Controller::setSoundVolume((int)guiElements[i]->getValue());
		}
		else if (guiElements[i]->label.getString() == "Resolution") {
			Controller::setResolutionID((int)guiElements[i]->getValue());
		}
	}
}

void MainMenu::initFileNamesToLoad(vector<string> fileNames, Theme* theme)
{
	fileNamesToLoad.clear();
	for (unsigned int i = 0; i < fileNames.size(); i++) {
		fileNamesToLoad.push_back(fileNames[i]);
	} // populate array fileNameToLoad in order to load the sprites

	setMenuSprites(theme);
}

void MainMenu::setMenuSprites(Theme* theme)
{
	const unsigned int NUMBER_OF_SPRITES = fileNamesToLoad.size();
	
	/*
		Adds Sprites to vector and trims them
		Render region in which they will be placed
		Set Position of Sprites 
		Add Sprites into drawStack and tabOrder sets
	*/
	vector<Vector2f> dimensions;
	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++)
	{
		Sprite* buffer = new Sprite(TextureHolder::GetTexture(fileNamesToLoad[i]), IntRect(0, 0, 256, 64));
		dimensions.push_back(Vector2f(buffer->getLocalBounds().width, buffer->getLocalBounds().height));  // get dimensions of Sprites needed by the region
		drawStack[drawStack.size() + 2] = buffer;  // add items to the draw stack (details for ordering in GameMenu.h)
		tabOrder[tabOrder.size()] = make_pair("SP",buffer); // add items to the tabOrder
		menuSprites.push_back(buffer); // add Sprites to the menuSprites
	}

	vector<Vector2f> newPositions = theme->renderRegion(dimensions); // render elements in region. FloatRect is used as a wrapper
	for (unsigned int i = 0; i < NUMBER_OF_SPRITES; i++) {
		menuSprites[i]->setPosition(newPositions[i]);
	}
	menuSprites[0]->setTextureRect(IntRect(256, 0, 256, 128)); // set NewGame as Default Selected
}


void MainMenu::loadTextGraphics(vector<string> textsArray, Theme* theme)
{
	vector<Vector2f> dimensions;
	for (unsigned int i = 0; i < textsArray.size(); i++) {
		Text* buffer = new Text(textsArray[i], font, 24);
		menuTexts.push_back(buffer);
		dimensions.push_back(Vector2f(buffer->getLocalBounds().width, buffer->getLocalBounds().height));
		drawStack[drawStack.size() + 2] = buffer;
		tabOrder[tabOrder.size()] = make_pair("TXT", buffer);
		buffer->setFillColor(Color::White);
	} 
	vector<Vector2f> newPositions = theme->renderRegion(dimensions);
	for (unsigned int i = 0; i < textsArray.size(); i++) {
		menuTexts[menuTexts.size() - textsArray.size() + i]->setPosition(newPositions[i]);
	}
	if (tabOrder.size() == menuTexts.size())
		menuTexts[0]->setFillColor(Color::Red); //set as default selected
}

void MainMenu::animate() {
	const float ANIMATION_SPEED = 0.3f;
	if (menuSprites.size() != 0 && tabOrder[optionSelected].first=="SP")
	{
		if (totalTimePassed > ANIMATION_SPEED) 
		{
			totalTimePassed -= ANIMATION_SPEED;
			int left = menuSprites[optionSelected]->getTextureRect().left; // get left position of previous selected texture
			left = left == 256 ? 512 : 256;
			menuSprites[optionSelected]->setTextureRect(IntRect(left, 0, 256, 64));
		}
	}

}

void MainMenu::changeSeletedOption(int direction) 
{	
	// Disgusting but it works...
	if (tabOrder[optionSelected].first == "TXT") {
		((Text*)tabOrder[optionSelected].second)->setFillColor(Color::White);
	}
	else if (tabOrder[optionSelected].first == "SP") {
		((Sprite*)tabOrder[optionSelected].second)->setTextureRect(IntRect(0, 0, 256, 64));
	} 
	else if (tabOrder[optionSelected].first == "GUI") {
		((GuiElement*)tabOrder[optionSelected].second)->unSelect();
	}
	optionSelected += (tabOrder.size() + direction);
	optionSelected = optionSelected % tabOrder.size();

	if (tabOrder[optionSelected].first == "TXT") {
		((Text*)tabOrder[optionSelected].second)->setFillColor(Color::Red);
	} 
	else if (tabOrder[optionSelected].first == "SP") {
		((Sprite*)tabOrder[optionSelected].second)->setTextureRect(IntRect(256, 0, 256, 64));
	} 
	else if (tabOrder[optionSelected].first == "GUI") {
		((GuiElement*)tabOrder[optionSelected].second)->setSelected();
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

	saveFile.close();
	loadTextGraphics(saveFilesArray, new MainMenuWindow(true,false));
	saveFilesArray.clear();

}

void MainMenu::initOptions(Theme* theme)
{

	ValueBar* buffer = new ValueBar(m_window, Text("Music Volume", font, 30), font, theme, (float)Controller::getMusicVolume());
	guiElements.push_back(buffer);
	drawStack[2 + drawStack.size()] = buffer;
	tabOrder[tabOrder.size()] = make_pair("GUI", buffer);

	buffer = new ValueBar(m_window, Text("Sound Volume", font, 30), font, theme, (float)Controller::getSoundVolume());
	guiElements.push_back(buffer);
	drawStack[2 + drawStack.size()] = buffer;
	tabOrder[tabOrder.size()] = make_pair("GUI", buffer);
	
	vector<pair<string, string>> resolutions; 
	for (Vector2u res : Controller::getAvailableResolutions()) 
	{
		resolutions.push_back(make_pair(to_string(res.x), to_string(res.y)));
	}
	OptionBox* opBuffer = new OptionBox(m_window, Text("Resolution", font, 30), font, theme, Controller::getResolutionID(), resolutions);
	guiElements.push_back(opBuffer);
	drawStack[2 + drawStack.size()] = opBuffer;
	tabOrder[tabOrder.size()] = make_pair("GUI", opBuffer);

	vector<Vector2f> dimensions;
	for (GuiElement * ge : guiElements) {
		dimensions.push_back(ge->getDimensions());
	}
	vector<Vector2f> newPositions = theme->renderRegion(dimensions);
	for (unsigned int i = 0; i < guiElements.size(); i++) {
		guiElements[i]->setPosition(newPositions[i]);
	}

	optionSelected = 0;
	guiElements[0]->setSelected();

}
