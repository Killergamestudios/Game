#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "textureHolder.h"

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

private:
	void init(); // Initializes everything
	void clearData(); // Deletes everything. Called inside init()
	template <size_t N>
	void initFileNamesToLoad(const string (&fileNames)[N]);
	void setMenuSprites();
	bool actions(int optionSelected, int &indexFileToLoad);
	void animate(float &totaltimepassed,int optionSelected); //Handles the animation of menu buttons
	void fadeInMusic(Music &music);

	// necessary globals
	Music *backgroundMusic; // Background music for menu
	Sprite *title; // used for emblem and game title
	float opacity; // nedded for fade in animation
	int optionSelected;
	int index; // the option that was selected
	int depth; // the depth in the main menu that you are currently
	float totalTimePassed; // needed for animation
	// ---------------

	RenderWindow* m_window; // DONT DELETE
	map<string,string> *returnState; // DONT DELETE 
	
	vector<Sprite> menuSprites; // doesnt get deleted
	vector<string> fileNamesToLoad; // path of sprites for to load
	const string mainMenu[4] =
	{
		"./graphics/interfaces/MainMenu/NewGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/LoadGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/OptionsButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/CreditsButtons-Sheet.png"
	};    // paths of mainMenuButtons

};

