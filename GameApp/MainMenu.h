#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"

using namespace sf;

enum MainMenuState {opening,Main,newGame,LoadGame,Options,credits};

class MainMenu
{
public:
	MainMenu(RenderWindow &window);
	~MainMenu();
	void boot();
	int menu();
	

private:
	void init();

	template <size_t N>
	void initFileNamesToLoad(const string (&fileNames)[N]);
	
	void setMenuSprites();
	void draw();
	bool actions(int optionSelected, int &indexFileToLoad);
	void animate(float &totaltimepassed,int optionSelected); //Handles the animation of menu buttons

	Font font;
	RenderWindow* m_window;
	MainMenuState m_state;
	vector<Text> textArray;
	vector<Sprite> menuSprites;
	vector<string> fileNamesToLoad; // path of sprites for to load
	const string mainMenu[4] =
	{
		"./graphics/interfaces/MainMenu/NewGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/LoadGameButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/OptionsButtons-Sheet.png",
		"./graphics/interfaces/MainMenu/CreditsButtons-Sheet.png"
	};    // paths of mainMenuButtons

};

