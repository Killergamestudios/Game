#pragma once
#include "../../../Header Files/Core/Engine.h"
void Engine::draw() {
	m_window.clear();
	vector<Sprite> Highlighted_tyles = InputController::getHighlighted_tyles();
	switch (Controller::getState()) {
	case Controller::BOOTING:
		mainmenu->draw();
		break;
	case Controller::IN_MENU:
		mainmenu->draw();
		break;
	case Controller::PLAYING:
		m_map->draw();
		m_window.draw(tile_sprite);
		if (Highlighted_tyles.size() != 0) {
			for (unsigned int i = 0; i < Highlighted_tyles.size(); i++)
				m_window.draw(Highlighted_tyles[i]);
		}
		/*for (unsigned int i = 0; i < party.size(); i++) {
			party[i].Draw();
		}*/
		//InputController::drowParty();
		ObjectContainer::drowParty();
		break;
	case Controller::LOADING:
		break;
	case Controller::IN_CUT_SCENE:
		break;
	}

	if (Controller::isSecondaryInitialized(Controller::IN_GAME_MAIN_MENU))
	{
		mainmenu->draw();
	}
	if (Controller::isSecondaryInitialized(Controller::CHARACTER_MENU))
	{
		characterMenu->draw();
	}

	m_window.setView(camera);
	m_window.display();

}