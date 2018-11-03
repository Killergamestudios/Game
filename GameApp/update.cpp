#include "pch.h"
#include "Engine.h"
void Engine::update(float dtAsSeconds) {
	switch(m_state){
	case State::Booting:
		mainmenu->updateBoot();
		break;
	case State::InMenu:
		mainmenu->updateMenu(dtAsSeconds);
		break;
	case State::Playing:
		break;
	case State::Loading:
		break;
	case State::Incutscene:
		break;
	}
}