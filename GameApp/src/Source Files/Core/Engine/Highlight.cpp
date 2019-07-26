#pragma once
#include "../../../Header Files/Core/InputCotroller.h"
#include "../../../Header Files/Objects/object.h"
#include "../../../Header Files/Core/Algorithms.h"
#include "../../../Header Files/Core/Controller.h"
#include "../../../Header Files/Objects/ObjectContainer.h"

vector<Vector3i> InputController::HighlightSpaces(CharacterObject * character)
{
	Vector2i myPos = character->getMyPosition();
	int MovementCost = character->getMovementCost();
	int ActionsRemaining = character->getActionsRemaining();

	Vector2i CurrentTyle;// the tyle that we want to highlight
	int MovementRange = ActionsRemaining / MovementCost; // get movementrange
	//int MovementRange = 2;
	//int attackRange = character->getWeaponRange();
	int attackRange = 1;
	vector<Vector3i> availableTyles = getAllAvailableTiles(myPos.x, myPos.y, MovementRange + attackRange, *Controller::getMap()); //get all the available tyles

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
				m_s_Instance->Highlighted_Tyles.push_back(sprite);
			}
			else if (Controller::getMap()->getFriendlyinPosition(CurrentTyle)) { // there is a friendly there
				Sprite sprite;
				sprite.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MovementTyles.png"));
				sprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); //Set it to green
				sprite.setPosition((float)(CurrentTyle.x * 64), (float)(CurrentTyle.y * 64));// set position of the sprite
				m_s_Instance->Highlighted_Tyles.push_back(sprite);
			}
			else {
				if (availableTyles[i].z > MovementRange && availableTyles[i].z <= attackRange + MovementRange) { // cant move there but can attack
					Sprite sprite;
					sprite.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MovementTyles.png"));
					sprite.setTextureRect(sf::IntRect(0, 64, 64, 64)); //Set it to red
					sprite.setPosition((float)(CurrentTyle.x * 64), (float)(CurrentTyle.y * 64));// set position of the sprite
					m_s_Instance->Highlighted_Tyles.push_back(sprite);

				}
				else {
					Sprite sprite;
					sprite.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MovementTyles.png"));
					sprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); //Set it to blue
					sprite.setPosition((float)(CurrentTyle.x * 64), (float)(CurrentTyle.y * 64));// set position of the sprite
					m_s_Instance->Highlighted_Tyles.push_back(sprite);
					ret.push_back(availableTyles[i]);
				}
			}
		}
	}
	return ret;
}

void InputController::UnHiglightSpaces()
{
	for (int i = m_s_Instance->Highlighted_Tyles.size() - 1; i >= 0; i--)
		m_s_Instance->Highlighted_Tyles.pop_back();
}

void InputController::SelectHighlight()
{
	if (m_s_Instance->mousePosition.x < 0 || m_s_Instance->mousePosition.y < 0 || m_s_Instance->mousePosition.x >= m_s_Instance->mapWidth/64 || m_s_Instance->mousePosition.y >= m_s_Instance->mapHeight/64) return;
	if (Controller::getMap()->getFriendlyinPosition(m_s_Instance->mousePosition) != 0) {
		if (!m_s_Instance->SelectingCharacter) {
			m_s_Instance->UnHiglightSpaces();
			int i = Controller::getMap()->getAllyVectorPosition(m_s_Instance->mousePosition);
			if (i != -1) {
				//m_s_Instance->HoveredCharacter = &m_s_Instance->party[i];
				m_s_Instance->HoveredCharacter = ObjectContainer::GetPartyMember(i);
				m_s_Instance->CharacterIndex = i;
			}

			if (!m_s_Instance->HoveredCharacter) {
				return;
			}
			m_s_Instance->availableSpaces = m_s_Instance->HighlightSpaces(m_s_Instance->HoveredCharacter);
			m_s_Instance->HoveringCharacter = true;
		}
	}
	/*else if (Controller::getMap()->getEnemyinPosition(mousePosition) != 0) {
		selectedCharacter = Controller::getMap()->getenemy(mousePosition);
		HighlightSpaces(selectedCharacter);

	}
	*/
	else {
		if (!m_s_Instance->SelectingCharacter) {
			m_s_Instance->HoveringCharacter = false;
			m_s_Instance->HoveredCharacter = nullptr;
			m_s_Instance->UnHiglightSpaces();
			m_s_Instance->CharacterIndex = -1;

			for (int i = m_s_Instance->availableSpaces.size() - 1; i >= 0; i--)
				m_s_Instance->availableSpaces.pop_back();
		}
	}

}

void InputController::CharacterDiraction(CharacterObject * SelectedCharacter)
{
	Vector2i pos = SelectedCharacter->getMyPosition();
	int dx = m_s_Instance->mousePosition.x - pos.x;
	int dy = m_s_Instance->mousePosition.y - pos.y;
	if (abs(dy) < abs(dx)) {
		if (dx < 0)
		{
			SelectedCharacter->SetDirection(FacingDirection::fleft);
		}
		else if (dx >= 0)
		{
			SelectedCharacter->SetDirection(FacingDirection::fright);
		}
	}
	else if (abs(dx) < abs(dy))
	{
		if (dy < 0)
		{
			SelectedCharacter->SetDirection(FacingDirection::back);
		}
		else if (dy >= 0)
		{
			SelectedCharacter->SetDirection(FacingDirection::front);
		}
	}
}

bool InputController::setCharacter() {
	int playerID = ObjectContainer::getAllyVectorInPosition(m_s_Instance->mousePosition);
	if (playerID != -1) {
		m_s_Instance->Character = m_s_Instance->HoveredCharacter = ObjectContainer::GetPartyMember(playerID);
		return true;
	}
	else {
		m_s_Instance->Character = nullptr;
		cout << "No character found" << endl;
		return false;
	}
}

CharacterObject* InputController::getCharacter() {
	return m_s_Instance->Character;
}