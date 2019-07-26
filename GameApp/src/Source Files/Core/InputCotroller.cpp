#include "../../Header Files/Core/InputCotroller.h"
#include <assert.h>
#include <windows.h>
#include "../../Header Files/Core/Algorithms.h"
#include "../../Header Files/Core/Controller.h"
#include "../../Header Files/Objects/ObjectContainer.h"

InputController* InputController::m_s_Instance = nullptr;

InputController::InputController()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}



void InputController::MoveCharacter()
{
	Vector2i pos = m_s_Instance->SelectedCharacter->getMyPosition();

	if (!m_s_Instance->CanMoveThere()) {

		m_s_Instance->CharacterMoving = false;
		m_s_Instance->SelectingCharacter = true;
		return;
	}
	int temp = 10000;
	vector<Vector2i> path = getPath(pos.x, pos.y, m_s_Instance->mousePosition.x, m_s_Instance->mousePosition.y, temp, *Controller::getMap());
	path.pop_back();
	std::reverse(path.begin(), path.end());

	ObjectContainer::MovePartyMember(m_s_Instance->CharacterIndex, path);
	//m_s_Instance->SelectedCharacter->MoveToPosition(path);
	m_s_Instance->SelectedCharacter = nullptr;
	m_s_Instance->CharacterMoving = false;

	//clear the vector
	for (int i = m_s_Instance->availableSpaces.size() - 1; i >= 0; i--)
		m_s_Instance->availableSpaces.pop_back();
}

bool InputController::CanMoveThere()
{
	for (unsigned int i = 0; i < m_s_Instance->availableSpaces.size(); i++) {
		if (m_s_Instance->availableSpaces[i].x == m_s_Instance->mousePosition.x && m_s_Instance->availableSpaces[i].y == m_s_Instance->mousePosition.y) return true;
	}
	return false;
}

void InputController::setMapDementions(Vector2f dim)
{
	m_s_Instance->mapWidth = dim.x;
	m_s_Instance->mapHeight = dim.y;
}

void InputController::getmousePosition(Vector2i pos)
{
	m_s_Instance->mousePosition = pos;
}

void InputController::MovingCharacterUpdate()
{
	if (m_s_Instance->SelectingCharacter) {
		m_s_Instance->CharacterDiraction();
	}
	if (m_s_Instance->CharacterMoving) {
		m_s_Instance->MoveCharacter();
	}
}

void InputController::Init()
{
	m_s_Instance->PlayerClicked = false;
	m_s_Instance->SelectingCharacter = false;
	m_s_Instance->SelectedCharacter = nullptr;
	m_s_Instance->HoveredCharacter = nullptr;
	m_s_Instance->HoveringCharacter = false;
	m_s_Instance->CharacterMoving = false;
	m_s_Instance->Character = nullptr;
}

/*void InputController::SetParty()
{
	m_s_Instance->party = Controller::getMap()->getparty();
}
*/
void InputController::setPlayerClicked()
{
	if (!m_s_Instance->PlayerClicked) m_s_Instance->PlayerClicked = true;
}

void InputController::HandlePlayerInput()
{
	if (m_s_Instance->PlayerClicked) {
		if (m_s_Instance->SelectedCharacter == nullptr) {
			if (!m_s_Instance->CharacterMoving)
				m_s_Instance->SelectedCharacter = m_s_Instance->HoveredCharacter;
			if (m_s_Instance->SelectedCharacter)
				m_s_Instance->SelectingCharacter = true;
		}
		else {
			if (m_s_Instance->mousePosition.x >= 0 && m_s_Instance->mousePosition.y >= 0 && m_s_Instance->SelectedCharacter != nullptr) {
				m_s_Instance->CharacterMoving = true;
				m_s_Instance->SelectingCharacter = false;
			}
		}
		m_s_Instance->PlayerClicked = false;
	}
}

vector<Sprite> InputController::getHighlighted_tyles()
{
	return m_s_Instance->Highlighted_Tyles;
}

/*void InputController::drowParty()
{
	for (unsigned int i = 0; i < m_s_Instance->party.size(); i++) {
		m_s_Instance->party[i].Draw();
	}
}

void InputController::UpdateParty(float dtasseconds)
{
	for (unsigned int i = 0; i < m_s_Instance->party.size(); i++) {
		m_s_Instance->party[i].update(dtasseconds);
	}
}
*/
