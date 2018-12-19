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
				controlUnit["Running"] = "False";
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
					mainmenu->actions();
				}
			}

			if (evt.type == Event::KeyPressed) {
				keyPressed = true;
			}
			break;
		case State::Playing:
			
			if (evt.type == Event::KeyReleased) {
				keyPressed = false;
			}

			if (!keyPressed || overrideKeyPressed > CAMERA_UPDATE_SPEED)
			{
				overrideKeyPressed = 0;
				if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
				{
					cameraUpdate(-1);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
				{
					cameraUpdate(1);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
				{
					cameraUpdate(-2);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
				{
					cameraUpdate(2);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Escape))
				{	
					if (controlUnit["InGameMenu"] == "")
					{
						mainmenu->initMenu();
						controlUnit["InGameMenu"] = "True";
					} 
					else 
					{
						controlUnit["InGameMenu"] = "";
						controlUnit["Running"] = "False";
					}
				}
			}
			
			if (evt.type == Event::KeyPressed) {
				keyPressed = true;
			}

			break;
		case State::Loading:
			break;
		case State::Incutscene:
			break;
		}


		//to close the window (for now)
		if (evt.type == Event::KeyPressed)
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) 
				m_window.close();
	
	}
}