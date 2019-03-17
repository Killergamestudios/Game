#pragma once
#include "../../../Header Files/Core/Engine.h"
#include "../../../Header Files/Objects/object.h"
#include "../../../Header Files/Core/Algorithms.h"
#include "../../../Header Files/Core/Controller.h"

vector<Vector3i> Engine::HighlightSpaces(CharacterObject * character)
{
	Vector2i myPos = character->getMyPosition();
	int MovementCost = character->getMovementCost();
	int ActionsRemaining = character->getActionsRemaining();

	Vector2i CurrentTyle;// the tyle that we want to highlight
	//int MovementRange = ActionsRemaining / MovementCost; // get movementrange
	int MovementRange = 2;
	//int attackRange = character->getWeaponRange();
	int attackRange = 1;
	vector<Vector3i> availableTyles = getAllAvailableTiles(myPos.x, myPos.y, MovementRange + attackRange, *Controller::getMap()); //get all the available tyles
	/*vector<Vector3i> availableTyles;
	availableTyles.push_back(Vector3i(myPos.x, myPos.y, 0));

	availableTyles.push_back(Vector3i(myPos.x + 1, myPos.y, 1));
	availableTyles.push_back(Vector3i(myPos.x, myPos.y + 1, 1));
	availableTyles.push_back(Vector3i(myPos.x - 1, myPos.y , 1));
	availableTyles.push_back(Vector3i(myPos.x, myPos.y - 1, 1));

	availableTyles.push_back(Vector3i(myPos.x + 2, myPos.y, 2));
	availableTyles.push_back(Vector3i(myPos.x - 2, myPos.y, 2));
	availableTyles.push_back(Vector3i(myPos.x, myPos.y + 2, 2));
	availableTyles.push_back(Vector3i(myPos.x, myPos.y - 2, 2));
	availableTyles.push_back(Vector3i(myPos.x + 1, myPos.y + 1, 2));
	availableTyles.push_back(Vector3i(myPos.x + 1, myPos.y - 1, 2));
	availableTyles.push_back(Vector3i(myPos.x - 1, myPos.y + 1, 2));
	availableTyles.push_back(Vector3i(myPos.x - 1, myPos.y - 1, 2));
	*/
	vector<Vector3i> ret;
	for (unsigned int i = 0; i < availableTyles.size(); i++) {
		CurrentTyle.x = availableTyles[i].x; CurrentTyle.y = availableTyles[i].y; // get the tyle to highlight
		if (!(Controller::getMap()->getMapWidth() / 64 <= CurrentTyle.x || Controller::getMap()->getMapHeight() / 64 <= CurrentTyle.y || CurrentTyle.x < 0 || CurrentTyle.y < 0))
		{
			if (Controller::getMap()->getEnemyinPosition(CurrentTyle) != 0) { // there is an enemy there
				Sprite sprite;
				sprite.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MovementTyles.png"));
				sprite.setTextureRect(sf::IntRect(0, 64, 64, 64)); //Set it to red
				sprite.setPosition((float)(CurrentTyle.x * 64), (float)(CurrentTyle.y * 64));// set position of the sprite
				Highlighted_Tyles.push_back(sprite);
			}
			else if (Controller::getMap()->getFriendlyinPosition(CurrentTyle)) { // there is a friendly there
				Sprite sprite;
				sprite.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MovementTyles.png"));
				sprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); //Set it to green
				sprite.setPosition((float)(CurrentTyle.x * 64), (float)(CurrentTyle.y * 64));// set position of the sprite
				Highlighted_Tyles.push_back(sprite);
			}
			else {
				if (availableTyles[i].z > MovementRange && availableTyles[i].z <= attackRange + MovementRange) { // cant move there but can attack
					Sprite sprite;
					sprite.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MovementTyles.png"));
					sprite.setTextureRect(sf::IntRect(0, 64, 64, 64)); //Set it to red
					sprite.setPosition((float)(CurrentTyle.x * 64), (float)(CurrentTyle.y * 64));// set position of the sprite
					Highlighted_Tyles.push_back(sprite);

				}
				else {
					Sprite sprite;
					sprite.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MovementTyles.png"));
					sprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); //Set it to blue
					sprite.setPosition((float)(CurrentTyle.x * 64), (float)(CurrentTyle.y * 64));// set position of the sprite
					Highlighted_Tyles.push_back(sprite);
					ret.push_back(availableTyles[i]);
				}
			}
		}
	}
	return ret;
}

void Engine::UnHiglightSpaces()
{
	for (int i = Highlighted_Tyles.size() - 1; i >= 0; i--)
		Highlighted_Tyles.pop_back();
}

void Engine::SelectHighlight()
{
	if (mousePosition.x < 0 || mousePosition.y < 0 || mousePosition.x >= mapWidth/64 || mousePosition.y >= mapHeight/64) return;
	if (Controller::getMap()->getFriendlyinPosition(mousePosition) != 0) {
		if (!SelectingCharacter) {
			UnHiglightSpaces();
			int i = Controller::getMap()->getAllyVectorPosition(mousePosition);
			if (i != -1)
				HoveredCharacter = &party[i];
			if (!HoveredCharacter) {
				return;
			}
			availableSpaces = HighlightSpaces(HoveredCharacter);
			HoveringCharacter = true;
		}
	}
	/*else if (Controller::getMap()->getEnemyinPosition(mousePosition) != 0) {
		selectedCharacter = Controller::getMap()->getenemy(mousePosition);
		HighlightSpaces(selectedCharacter);

	}
	*/
	else {
		if (!SelectingCharacter) {
			HoveringCharacter = false;
			HoveredCharacter = nullptr;
			UnHiglightSpaces();

			for (int i = availableSpaces.size() - 1; i >= 0; i--)
				availableSpaces.pop_back();
		}
	}

}
