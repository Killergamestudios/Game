#include "pch.h"
#include "Engine.h"
#include <iostream>
void Engine::update(float dtAsSeconds) {
	switch(m_state){
	case State::Booting:
		mainmenu->updateBoot();
		break;
	case State::InMenu:
		mainmenu->updateMenu(dtAsSeconds);
		break;
	case State::Playing:
		if(controlUnit["InGameMenu"] == "True")
			mainmenu->updateMenu(dtAsSeconds);
		for (unsigned int i = 0; i < party.size(); i++) {
			party[i].update(dtAsSeconds);
		}
>>>>>>>>> Temporary merge branch 2
		break;
	case State::Loading:
		break;
	case State::Incutscene:
		break;
	}
}