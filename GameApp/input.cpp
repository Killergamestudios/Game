#include "pch.h"
#include "Engine.h"

void Engine::input(float dtAsSeconds) {
	Event evt;
	overrideKeyPressed += dtAsSeconds;
	while (m_window.pollEvent(evt)) {
		switch (m_state) {
		case State::Booting:
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				controlUnit["Running"] = "false";
			}
			break;
		case State::InMenu:
			
			if (evt.type == Event::KeyReleased) {
				keyPressed = false;
			}

			if (!keyPressed || overrideKeyPressed > CHANGE_SELECTION_SPEED)
			{
				overrideKeyPressed = 0;
				if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
				{
					mainmenu->changeSeletedOption(-1);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
				{
					mainmenu->changeSeletedOption(1);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					// TODO : change state or do something
					//if (!actions(optionSelected, indexFileToLoad))
					//{
					//	break;
					//}
				}
			}
			
			if (evt.type == Event::KeyPressed) {
				keyPressed = true;
			}

			break;
		case State::Playing:
			break;
		case State::Loading:
			break;
		case State::Incutscene:
			break;
		}


		//to close the window (for now)
		if (evt.type == Event::KeyPressed)
		
			if (Keyboard::isKeyPressed(Keyboard::Escape)) 
				m_window.close();
	
	}
}