#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "textureHolder.h"
#include "fstream"
using namespace sf;

//enum MainMenuState {opening,Main,newGame,LoadGame,Options,credits};

class MainMenu
{
public:
	MainMenu(RenderWindow &window, map<string, string> &controlUnit);
	~MainMenu();
	
	void initBoot();
	void updateBoot();
	void drawBoot();

	void initMenu();
	void updateMenu(float);
	void drawMenu();
	void changeSeletedOption(int direction);
	void actions();

private:
	void init(); // Initializes everything
	void clearData(); // Deletes everything. Called inside init()
	void clearTextures(); // Clears menuTextures in menu transitions
	void initFileNamesToLoad(vector<string> fileNames);
	void setMenuSprites();
	void loadTextGraphics(vector<string> textsArray);
	void animate(float &totaltimepassed,int optionSelected); //Handles the animation of menu buttons
	void fadeInMusic(Music &music);
	void loadSaveFiles();

	// necessary globals
	Music *backgroundMusic; // Background music for menu
	Sprite *title; // used for emblem and game title
	float opacity; // nedded for fade in animation
	int optionSelected; // show the currently selected menu item
	int index; // the option that was selected
	int depth; // the depth in the main menu that you are currently
	float totalTimePassed; // needed for animation
	Font font; // Font for text
	// ---------------

	// variables for loading games
	ifstream saveFile; // used to oped save files
	vector<string> loadFilePath; // path for load game files

	RenderWindow* m_window; // DONT DELETE
	map<string,string> *returnState; // DONT DELETE 

	vector<Text> menuTexts; // text for menu entries (load game files)
	
	vector<Sprite> menuSprites; // sprites for menu items
	vector<string> fileNamesToLoad; // path of sprites for to load
	const vector<string> mainMenu =
	{
		"./graphics/interfaces/MainMenu/NewGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/LoadGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/OptionsButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/CreditsButtons-Sheet.png"
	};    // paths of mainMenuButtons (depth = 0)

};

