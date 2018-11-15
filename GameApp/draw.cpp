#include "pch.h"
#include "Engine.h"
void Engine::draw() {
	m_window.clear();
	switch (m_state) {
	case State::Booting:
		mainmenu->drawBoot();
		break;
	case State::InMenu:
		mainmenu->drawMenu();
		break;
	case State::Playing:
		m_map->draw();
		break;
	case State::Loading:
		break;
	case State::Incutscene:
		break;
	}
	m_window.setView(camera);
	m_window.display();
}