#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Core/textureHolder.h"
#include "fstream"
#include "MainMenu.h"
using namespace sf;

class InGameMainMenu : public MainMenu
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
	void initLayer(); // Initializes everything
	void loadTextGraphics(vector<string> fileNames); // get the files names for sprite
	void loadSaveFiles(); // handles the loading of all save files
	void changeSeletedOption(int direction); // changes selected option
	void setBackgroundSprites(vector<string> backgroundSpritesPath);
	void clearTextures();
	void initOptions(); // initializes options menu
	
	

	int optionSelected; // show the currently selected menu item
	float totalTimePassed; // needed for animation
	int depth; // the depth in the main menu that you are currently
	bool loadMenu; // shows if player is in load menu
	unsigned const int NUMBER_OF_ENTRIES_PER_PAGE = 4; // TODO

	// variables for loading games
	ifstream saveFile; // used to oped save files
	vector<string> loadFilePath; // path for load game files

	vector<Text*> menuTexts; // text for menu entries (load game files)

	vector<Sprite*> menuSprites; // sprites for menu items
	RectangleShape *backgroundFillColor;
	
	vector<Sprite*> backgroundSprites; // sprites for background images 
	const vector<string> mainMenu =
	{
		"RESUME  GAME",
		"LOAD  GAME",
		"GAME  OPTIONS",
		"QUIT  GAME"
	};    // names of in game main menu entries (depth = 0)

	const vector<string> backgroundSpritesPath =
	{
		"./graphics/interfaces/MainMenu/PopupMainMenuBackgroundBorder.png"
	};
};

