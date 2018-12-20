#pragma once
#include "pch.h"
#include "Engine.h"
void Engine::draw() {
	m_window.clear();
	switch (Controller::getState()) {
	case Controller::BOOTING:
		mainmenu->draw();
		break;
	case Controller::IN_MENU:
		mainmenu->draw();
		break;
	case Controller::PLAYING:
		m_map->draw();
		for (unsigned int i = 0; i < party.size(); i++) {
			party[i].Draw();
		}
		break;
	case Controller::LOADING:
		break;
	case Controller::IN_CUT_SCENE:
		break;
	}
	m_window.setView(camera);
	m_window.display();

	if (Controller::isSecondaryInitialized(Controller::IN_GAME_MAIN_MENU))
	{
		mainmenu->draw();
	}
}