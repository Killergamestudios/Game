#pragma once
#include "GameMenu.h"
#include "../Objects/object.h"
#include "Theme/CharacterWindow.h"
class CharacterMenu : public GameMenu
{
public:
	CharacterMenu(RenderWindow& window);//, CharacterObject& selectedCharacter);
	~CharacterMenu();
	void init() override;
	void update(float&) override;
	void draw() override;
	void input() override;
	void actions() override;

private:
	void initLayer();
	void clearTextures();
	void loadTextGraphics(vector<string> btns, vector<string> descriptions);
	void changeSeletedOption(int direction);

	int depth, descriptionIndex;
	float totalTimePassed;
	unsigned int optionSelected;
	CharacterObject* selectedCharacter;
	RectangleShape* backgroundFillColor;
	vector<string> textLayer1 = { "Move", "Stay", "Back" };
	vector<string> descLayer1 = {
		"Move character",
		"Remain on current position",
		"Leave Character Menu"
	};
	vector<string> textLayer2 = { "Attack", "Ability", "End Turn", "Undo Move" };
	vector<string> descLayer2 = {
		"Attack with weapon",
		"Perform character's special attack",
		"End your turn",
		"Reset character movement"
	};
	vector<Text*> menuTexts;
	CharacterWindow* theme;
	vector<pair<int, int>> previousPositions;
};
