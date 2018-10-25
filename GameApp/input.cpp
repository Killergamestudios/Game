#include "pch.h"
#include "ENGINE.h"

void Engine::input() {
	Event event;
	while (m_window.pollEvent(event)) {
		if (m_state == State::Playing) {

		}
		else if (m_state == State::InMenu) {

		}



		//to close the window (for now)
		if (event.type == Event::KeyPressed)
		
			if (Keyboard::isKeyPressed(Keyboard::Escape)) 
				m_window.close();
	
	}
}