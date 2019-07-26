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
		if (Controller::isSecondaryInitialized(Controller::IN_GAME_MAIN_MENU))
		{
			mainmenu->update(dtAsSeconds);
		}
		else if (Controller::isSecondaryInitialized(Controller::CHARACTER_MENU))
		{
			characterMenu->update(dtAsSeconds);
			if (!Controller::isSecondaryInitialized(Controller::CHARACTER_MENU))
				delete characterMenu;
		}
		else 
		{
			mouseAnimation(mouseTimePass, animState, mouseControl());
			ObjectContainer::UpdateParty(dtAsSeconds);
		}

		break;
	case Controller::LOADING:
		break;
	case Controller::IN_CUT_SCENE:
		break;
	}

	
}


