#pragma once
#include "../../../Header Files/Core/Engine.h"
#include <iostream>
#include "../../../Header Files/Core/Algorithms.h"

void Engine::update(float dtAsSeconds) {
	switch(Controller::getState()){
	case Controller::BOOTING:
		mainmenu->update(dtAsSeconds);
		break;
	case Controller::IN_MENU:
		mainmenu->update(dtAsSeconds);
		break;
	case Controller::PLAYING:
		mouseTimePass += dtAsSeconds;
		mouseAnimation(mouseTimePass, animState, mousePosition);
		if(SelectingCharacter)
			CharacterDiraction();
		if (CharacterMoving)
			MoveCharacter();

		for (unsigned int i = 0; i < party.size(); i++) {
			party[i].update(dtAsSeconds);
		}
		break;
	case Controller::LOADING:
		break;
	case Controller::IN_CUT_SCENE:
		break;
	}

	if (Controller::isSecondaryInitialized(Controller::IN_GAME_MAIN_MENU))
	{
		mainmenu->update(dtAsSeconds);
	}
}

void Engine::CharacterDiraction() {
	if (!SelectedCharacter) return;
	Vector2i pos = SelectedCharacter->getMyPosition();
	int dx = pos.x - mousePosition.x;
	int dy = pos.y - mousePosition.y;
	if (dx < 0 && dy > 0) { //
		if (abs(dx) > abs(dy))
			SelectedCharacter->SetDirection(FacingDirection::fright);
		else
			SelectedCharacter->SetDirection(FacingDirection::back);
	}
	else if (dx < 0 && dy < 0) {
		if(abs(dx) > abs(dy))
			SelectedCharacter->SetDirection(FacingDirection::fright);
		else
			SelectedCharacter->SetDirection(FacingDirection::front);
	}
	else if (dx > 0 && dy < 0) {
		if (abs(dx) > abs(dy))
			SelectedCharacter->SetDirection(FacingDirection::fleft);
		else
			SelectedCharacter->SetDirection(FacingDirection::front);
	}
	else if (dx > 0 && dy > 0) {
		if (abs(dx) > abs(dy))
			SelectedCharacter->SetDirection(FacingDirection::fleft);
		else
			SelectedCharacter->SetDirection(FacingDirection::back);
	}
}


void Engine::MoveCharacter() {
	Vector2i pos = SelectedCharacter->getMyPosition();

	if (!CanMoveThere()) {

		CharacterMoving = false;
		SelectingCharacter = true;
		return;
	}
	int temp = 10000;
	vector<Vector2i> path = getPath(pos.x, pos.y, mousePosition.x, mousePosition.y, temp, *Controller::getMap());
	path.pop_back();
	std::reverse(path.begin(), path.end());
	SelectedCharacter->MoveToPosition(path);
	SelectedCharacter = nullptr;
	CharacterMoving = false;

	//clear the vector
	for (int i = availableSpaces.size() - 1; i >= 0; i--)
		availableSpaces.pop_back();

}

bool Engine::CanMoveThere(){
	for (unsigned int i = 0; i < availableSpaces.size(); i++) {
		if (availableSpaces[i].x == mousePosition.x && availableSpaces[i].y == mousePosition.y) return true;
	}
	return false;
}