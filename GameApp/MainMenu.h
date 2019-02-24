#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "textureHolder.h"
#include "fstream"
#include "GameMenu.h"
#include "ValueBar.h"
#include "OptionBox.h"

using namespace sf;

class MainMenu : public GameMenu
{
public:
	MainMenu(RenderWindow &window);
	~MainMenu();
	
	void init() override;
	void draw() override;
	void update(float) override;
	void actions() override;
	void input() override;

private:
	void initData(); // Initializes everything
	void initFileNamesToLoad(vector<string> fileNames); // get the files names for sprites
	void setMenuSprites(); // set the sprites for main menu textures
	void loadTextGraphics(vector<string> textsArray); // load and set main menu texts
	void animate(float &totaltimepassed,int optionSelected); //Handles the animation of menu buttons
	void loadSaveFiles(); // handles the loading of all save files
	void initOptions(); // initializes options menu
	void changeSeletedOption(int direction); // changes selected option
	void clearTextures();
	
	
	
	// necessary globals
	Music *backgroundMusic; // Background music for menu
	Sprite *title; // used for emblem and game title
	float opacity; // nedded for fade in animation
	int optionSelected; // show the currently selected menu item
	int index; // the option that was selected
	int depth; // the depth in the main menu that you are currently
	float totalTimePassed; // needed for animation
	unsigned int buttonsCounter;
	// ---------------

	// variables for loading games
	ifstream saveFile; // used to oped save files
	vector<string> loadFilePath; // path for load game files

	vector<Text*> menuTexts; // text for menu entries (load game files)

	vector<Sprite*> menuSprites; // sprites for menu items
	vector<string> fileNamesToLoad; // path of sprites for to load

	vector<Sprite*> backgroundSprites; // sprites for background images 
	vector<GuiElement*> guiElements; // gui elements for forms (options menu)

	const vector<string> mainMenu =
	{
		"./graphics/interfaces/MainMenu/NewGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/LoadGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/OptionsButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/CreditsButtons-Sheet.png"
	};    // paths of mainMenuButtons (depth = 0)

	const vector<string> optionsMenu =
	{
		"Resolution",
		"Music Volume",
		"Sound Volume"
	};		// options menu


	// general purpose constants 
	const int WIN_HEIGHT = m_window->getSize().y;
	const int WIN_WIDTH = m_window->getSize().x;
	const float MARGIN_LOGO = WIN_HEIGHT * 0.05f; // top and down margin of logo
	const float BOTTOM_MARGIN = WIN_HEIGHT * 0.05f; // bottom margin
	const float HEIGHT_LOGO = WIN_HEIGHT * 0.3f; // to be initialized properly
	const float TOP_CONTAINER = 2 * MARGIN_LOGO + HEIGHT_LOGO;
};

