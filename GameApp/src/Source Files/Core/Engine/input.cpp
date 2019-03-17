#pragma once
#include "../../../Header Files/Core/Engine.h"

void Engine::input(float dtAsSeconds) {
	Event evt;
	overrideKeyPressed += dtAsSeconds;
	while (m_window.pollEvent(evt)) {
		if (Controller::isExecuteSecondary(Controller::IN_GAME_MAIN_MENU)) 
		{
			if (evt.type == Event::KeyReleased) 
			{
				keyPressed = false;
			}

			if (!keyPressed || overrideKeyPressed > CHANGE_SELECTION_SPEED)
			{
				overrideKeyPressed = 0;
				mainmenu->input();
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					Controller::setExecuteSecondary(Controller::IN_GAME_MAIN_MENU, false);
				}
			}

			if (evt.type == Event::KeyPressed) 
			{
				keyPressed = true;
			}
		}
		else 
		{
			switch (Controller::getState()) 
			{
			case Controller::BOOTING:
				mainmenu->input();
				break;
			case Controller::IN_MENU:

				if (evt.type == Event::KeyReleased) {
					keyPressed = false;
				}

				if (!keyPressed || overrideKeyPressed > CHANGE_SELECTION_SPEED)
				{
					overrideKeyPressed = 0;
					mainmenu->input();
				}

				if (evt.type == Event::KeyPressed) {
					keyPressed = true;
				}
				break;
			case Controller::PLAYING:

				mouseTimePass += dtAsSeconds;
				mousePosition = mouseControl(mouseTimePass, animState);
				SelectHighlight();



				if (evt.type == Event::KeyReleased) {
					keyPressed = false;
				}
				if (evt.type == Event::MouseButtonReleased) {
					MousePressed = false;
				}
				if (!MousePressed) {
					if (Mouse::isButtonPressed(Mouse::Left)) {
						if (SelectedCharacter == nullptr) {
							if(!CharacterMoving)
								SelectedCharacter = HoveredCharacter;
							SelectingCharacter = true;
						}
						else {
							if (mousePosition.x >= 0 && mousePosition.y >= 0 && SelectedCharacter != nullptr) {
								CharacterMoving = true;
								SelectingCharacter = false;
							}
						}
					}
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
						Controller::setExecuteSecondary(Controller::IN_GAME_MAIN_MENU, true);
					}
				}

				if (evt.type == Event::KeyPressed) {

					keyPressed = true;
					
				}
				if (evt.type == Event::MouseButtonPressed) {
					MousePressed = true;
				}

				break;
			case Controller::LOADING:
				break;
			case Controller::IN_CUT_SCENE:
				break;
			}
		}


		//to close the window (for now)
		if (evt.type == Event::KeyPressed)
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) 
				Controller::quit(&m_window);

	
	}
}