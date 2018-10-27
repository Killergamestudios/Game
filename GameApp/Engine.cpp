#include "pch.h"
#include "ENGINE.h"

Engine::Engine() {
	m_window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Game Name", Style::Fullscreen);
}

void Engine::run() {
	Clock clock;

	while (m_window.isOpen()) {
		Time dt = clock.restart();
		GameTimeTotal = dt;
		float dtAsSeconds = dt.asSeconds();
		switch (m_state) {
		case State::Loading:
			//load the level
			m_state = State::Playing;
			break;
		case State::Incutscene:
			//play the cutscene
			//check a flag to see if you switch to playing or loading (oppening cutscene or ending cutscene)
			//change the state
			break;
		case State::InMenu:
			//another enum witch tells witch menu we are in (one of the main menus, one of the input menus during the fight etc)
			//change the states to playing loading cutscene or another menu depending on last state
			break;
		}
		input();
		//update();
		//draw();

	}
}