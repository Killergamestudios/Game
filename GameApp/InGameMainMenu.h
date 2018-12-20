#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "textureHolder.h"
#include "fstream"
#include "GameMenu.h"
using namespace sf;

class InGameMainMenu : public GameMenu
{
public:
	InGameMainMenu(RenderWindow &window);
	~InGameMainMenu();

	void init() override;
	void draw() override;
	void update(float) override;
	void actions() override;
	void input() override;

private: 
	void initData(); // Initializes everything
	void clearTextures(); // Clears menuTextures in menu transitions
	void initMenuEnrties(vector<string> fileNames); // get the files names for sprites
	void setMenuSprites(); // set the sprites for main menu textures
	void loadTextGraphics(vector<string> textsArray); // load and set main menu texts
	void loadSaveFiles(); // handles the loading of all save files
	void changeSeletedOption(int direction); // changes selected option

	int optionSelected; // show the currently selected menu item
	float totalTimePassed; // needed for animation


	// variables for loading games
	ifstream saveFile; // used to oped save files
	vector<string> loadFilePath; // path for load game files

	vector<Text> menuTexts; // text for menu entries (load game files)

	vector<Sprite> menuSprites; // sprites for menu items
	vector<string> fileNamesToLoad; // path of sprites for to load

	vector<Sprite> backgroundSprites; // sprites for background images 
	const vector<string> mainMenu =
	{
		"Resume Game",
		"Load Game",
		"Options",
		"Quit Game"
	};    // names of in game main menu entries (depth = 0)

};

