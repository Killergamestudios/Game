#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Core/textureHolder.h"
#include "fstream"
#include "GameMenu.h"
#include "Gui/ValueBar.h"
#include "Gui/OptionBox.h"

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

protected:
	void initFileNamesToLoad(vector<string> fileNames, Theme::Regions region); // get the files names for sprites
	void setMenuSprites(Theme::Regions region); // set the sprites for main menu textures
	void loadTextGraphics(vector<string> textsArray, Theme::Regions region); // load and set main menu texts
	void animate(float &totaltimepassed, int optionSelected); //Handles the animation of menu buttons
	void loadSaveFiles(); // handles the loading of all save files
	void initOptions(Theme::Regions region, int pos); // initializes options menu
	void changeSeletedOption(int direction); // changes selected option
	void clearTextures();
	void initLayer(); // initializes each menu layer

	int optionSelected; // show the currently selected menu item
	int depth; // the depth in the main menu that you are currently
	float totalTimePassed; // needed for animation

	// variables for loading games
	ifstream saveFile; // used to oped save files
	vector<string> loadFilePath; // path for load game files

	vector<Text*> menuTexts; // text for menu entries (load game files)

	vector<Sprite*> menuSprites; // sprites for menu items
	vector<string> fileNamesToLoad; // path of sprites for to load
	vector<string> backButton; // the string for the backbutton (has to be a vector in order to be processed by setMenuSprites)
	vector<Sprite*> backgroundSprites; // sprites for background images 
	vector<GuiElement*> guiElements; // gui elements for forms (options menu)
	vector<Vector2f> dimensions;

private:
	// necessary globals
	Music *backgroundMusic; // Background music for menu
	Sprite *title; // used for emblem and game title
	float opacity; // nedded for fade in animation
	
	bool loadMenu; // shows if player is in load menu
	// ---------------

	

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
};

