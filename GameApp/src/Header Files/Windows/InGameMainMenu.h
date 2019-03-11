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
	void update(float) override;
	void actions() override;

protected:
	void initLayer(); // Initializes everything
	void loadTextGraphics(vector<string> fileNames); // get the files names for sprite
	void loadSaveFiles(); // handles the loading of all save files
	void setBackgroundSprites(vector<string> backgroundSpritesPath);
	void clearTextures();
	void initOptions(Theme::Regions region, int pos);
	void initMenu();

private:
	bool loadMenu; // shows if player is in load menu
	unsigned const int NUMBER_OF_ENTRIES_PER_PAGE = 4; // TODO
	RectangleShape *backgroundFillColor;
	

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

