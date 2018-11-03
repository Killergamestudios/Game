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
		break;
	case State::Loading:
		break;
	case State::Incutscene:
		break;
	}
	m_window.display();
}