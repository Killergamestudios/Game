#pragma once
#include <SFML/Graphics.hpp>
#include "../Objects/object.h"

using namespace sf;
using namespace std;


class InputController
{
public:
	InputController();
	static vector<Vector3i> HighlightSpaces(CharacterObject *character);
	static void UnHiglightSpaces();
	static void SelectHighlight();
	static void CharacterDiraction();
	static void MoveCharacter();
	static bool CanMoveThere();
	static void setMapDementions(Vector2f dim);
	static void getmousePosition(Vector2i pos);

	static bool setCharacter();
	static CharacterObject* getCharacter();

	static void MovingCharacterUpdate();
	static void Init();
	//static void SetParty();
	static void setPlayerClicked();
	static void HandlePlayerInput();
	static vector<Sprite> getHighlighted_tyles();

	//static void drowParty();
	//static void UpdateParty(float dtasseconds);
private:
	static InputController *m_s_Instance;
	
	bool PlayerClicked;
	float mapWidth;
	float mapHeight;
	//vector<CharacterObject> party;

	CharacterObject *Character;

	Vector2i mousePosition;
	CharacterObject *HoveredCharacter;
	CharacterObject *SelectedCharacter;
	int CharacterIndex;
	bool HoveringCharacter;
	bool SelectingCharacter;
	bool CharacterMoving;
	vector<Vector3i> availableSpaces; // a vector with all the positions the selected Character can go and the cost

	vector<Sprite> Highlighted_Tyles;// the tyles that get HighLighted when we select a character


};

