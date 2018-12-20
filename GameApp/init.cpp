#pragma once
#include "pch.h"
#include "Engine.h"

void Engine::init() {
	switch (Controller::getState()) {
	case Controller::BOOTING:
		if (!Controller::isInitialized()) {
			delete mainmenu; // delete previous instance
			mainmenu = new BootMenu(m_window);
			Controller::clearState();
			mainmenu->init();
		}
		break;

	case Controller::IN_MENU:
		//another enum witch tells witch menu we are in (one of the main menus, one of the input menus during the fight etc)
		//change the states to playing loading cutscene or another menu depending on last state
		if (!Controller::isInitialized()) {
			delete mainmenu; // delete previous instance
			mainmenu = new MainMenu(m_window);
			Controller::clearState();
			mainmenu->init();
		}
		break;
	case Controller::LOADING:
		initGameVariables(0); // Needs to be replaced!!!!

		m_map->load(mapIndex);
		m_map->loadParty(m_map, Controller::getSaveFileDirectory());
		party = m_map->getparty();
		Controller::clearState();
		Controller::setState(Controller::PLAYING);
		Controller::setInitialized(true);
		mapWidth = (float)m_map->getMapWidth();
		mapHeight = (float)m_map->getMapHeight();
		break;
	case Controller::IN_CUT_SCENE:
		//play the cutscene
		//check a flag to see if you switch to playing or loading (oppening cutscene or ending cutscene)
		//change the state
		break;
	}

	if (!Controller::isSecondaryInitialized(Controller::IN_GAME_MAIN_MENU) && Controller::isExecuteSecondary(Controller::IN_GAME_MAIN_MENU))
	{
		delete mainmenu; // delete previous instance
		Controller::clearState(false,true,Controller::IN_GAME_MAIN_MENU);
		mainmenu = new InGameMainMenu(m_window);
		mainmenu->init();
		Controller::setSecondaryInitialized(Controller::IN_GAME_MAIN_MENU, true);
	}
}