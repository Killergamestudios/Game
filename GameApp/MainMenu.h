#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "textureHolder.h"
#include "fstream"
#include "GameMenu.h"
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
	void fadeInMusic(Music &music); // Animation: fade in Music
	void loadSaveFiles(); // handles the loading of all save files
	void changeSeletedOption(int direction); // changes selected option

	// necessary globals
	Music *backgroundMusic; // Background music for menu
	Sprite *title; // used for emblem and game title
	float opacity; // nedded for fade in animation
	int optionSelected; // show the currently selected menu item
	int index; // the option that was selected
	int depth; // the depth in the main menu that you are currently
	float totalTimePassed; // needed for animation
	// ---------------

	// variables for loading games
	ifstream saveFile; // used to oped save files
	vector<string> loadFilePath; // path for load game files

	vector<Text> menuTexts; // text for menu entries (load game files)
	
	vector<Sprite> menuSprites; // sprites for menu items
	vector<string> fileNamesToLoad; // path of sprites for to load

	vector<Sprite> backgroundSprites; // sprites for background images 
	const vector<string> mainMenu =
	{
		"./graphics/interfaces/MainMenu/NewGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/LoadGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/OptionsButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/CreditsButtons-Sheet.png"
	};    // paths of mainMenuButtons (depth = 0)

};

