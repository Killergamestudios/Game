#pragma once
#include "../../../Header Files/Core/Engine.h"
#include <iostream>

void Engine::update(float dtAsSeconds) {
	switch(Controller::getState()){
	case Controller::BOOTING:
		mainmenu->update(dtAsSeconds);
		break;
	case Controller::IN_MENU:
		mainmenu->update(dtAsSeconds);
		break;
	case Controller::PLAYING:
		mouseControl();
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