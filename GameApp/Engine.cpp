#include "pch.h"
#include "Engine.h"
#include "textureHolder.h"
#include "fstream"

Engine::Engine() {
	m_window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Game Name", Style::Fullscreen);
}

void Engine::run() {
	Clock clock;
	m_map = new Map(m_window);
	mainmenu = new MainMenu(m_window,controlUnit);
	keyPressed = false;

	int indexFileToLoad = 0;
	m_state = State::Booting;

	while (m_window.isOpen()) {
		Time dt = clock.restart();
		GameTimeTotal = dt;
		float dtAsSeconds = dt.asSeconds();
		// Begin : Initialization Phase
		switch (m_state) {
		case State::Booting:
			//controlUnit = mainmenu->getResults();
			if (controlUnit["Initialized"] == "") {
				mainmenu->initBoot();
			}
			break;
			//m_state = State::InMenu;
			
		case State::InMenu:
			//another enum witch tells witch menu we are in (one of the main menus, one of the input menus during the fight etc)
			//change the states to playing loading cutscene or another menu depending on last state
			//controlUnit = mainmenu->getResults();
			if (controlUnit["Initialized"] == "") {
				mainmenu->initMenu();
				//m_state = State::Loading;
			}
			break;
		case State::Loading:
			initGameVariables(indexFileToLoad);

			m_map->load(mapIndex);
			m_state = State::Playing;
			break;
		case State::Incutscene:
			//play the cutscene
			//check a flag to see if you switch to playing or loading (oppening cutscene or ending cutscene)
			//change the state
			break;
		}
		// End : Initialization Phase

		input(dtAsSeconds); // handles all the input
		update(dtAsSeconds); // handles updates - animation etc
		draw(); // handles drawing 
		updateState(); // hanldes the change of State
	}
}

void Engine::updateState() 
{
	string newState = controlUnit["Next State"];
	if (newState != "")
	{
		if (newState == "InMenu") {
			m_state = State::InMenu;
		} else if (newState == "Loading") {
			m_state = State::Loading;
		} else if (newState == "Playing") {
			m_state = State::Playing;
		} else if (newState == "Incutscene") {
			m_state = State::Incutscene;
		}
		//cout << m_state << endl;
	}
}

void Engine::initGameVariables(int indexFileToLoad) {
	/*
	string fileAddress;
	ifstream myfile;

	fileAddress = "./saves/gameFile_" + to_string(indexFileToLoad) + ".txt";
	myfile.open(fileAddress);
	*/

	mapIndex = 0;
}
