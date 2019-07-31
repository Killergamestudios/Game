#pragma once
#include "GameMenu.h"
#include "Theme/CharacterWindow.h"
#include "../../Header Files/Core/InputCotroller.h"
#include "../Objects/ObjectContainer.h"
class CharacterMenu : public GameMenu
{
public:
	CharacterMenu(RenderWindow& window, CharacterObject* selectedCharacter);//, CharacterObject& selectedCharacter);
	~CharacterMenu();
	void init() override;
	void update(float&) override;
	void draw() override;
	void input() override;
	void actions() override;
	void mouseInput(Vector2i) override;

private:
	void initLayer();
	void clearTextures();
	void loadTextGraphics(vector<string> btns, vector<string> descriptions);
	void changeSeletedOption(int direction);
	void initMoveLayout();

	int depth, descriptionIndex;
	float totalTimePassed;
	bool moved;
	unsigned int optionSelected;
	CharacterObject* selectedCharacter;
	vector<Vector3i> availableTiles;
	vector<Sprite> highlighted_tiles;
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
		undoMovement
	};
	vector<Text*> menuTexts;
	CharacterWindow* theme;
	Vector2i initialPosition;
	FacingDirection initialDirection;

	const string undoMovement = "Reset character movement";
};

