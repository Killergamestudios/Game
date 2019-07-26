#pragma once
#include "../../../Header Files/Core/Engine.h"
#include "../../../Header Files/Core/textureHolder.h"
#include "fstream"

Engine::Engine() {

	// get resolution from ini file. Need casting to int
	viewWidth = (float)Controller::getResolutionWidth();
	viewHeight = (float)Controller::getResolitionHeight();
	windowWidth = (float)VideoMode::getDesktopMode().width;
	windowHeight =(float)VideoMode::getDesktopMode().height;
	m_window.create(VideoMode((unsigned int)windowWidth, (unsigned int)windowHeight), "Game Name", Style::Fullscreen);
	camera.setViewport(FloatRect((windowWidth - viewWidth) / 2 / windowWidth, (windowHeight - viewHeight) / 2 / windowHeight,
		viewWidth / windowWidth, viewHeight / windowHeight));
	camera.setCenter(Vector2f(viewWidth / 2, viewHeight / 2));
	camera.setSize(Vector2f(viewWidth, viewHeight));
	m_window.setView(camera);
	Controller::setWindow(&m_window);
	m_map = new Map(m_window);
	Controller::setMap(m_map);
	tile_sprite = Sprite(TextureHolder::GetTexture("./graphics/interfaces/tileSelectorAnimated.png")); //For the mouse Texture
	mouseTimePass = 0; //For the mouse animation
	animState = 0; //For the mouse animation

	
}

void Engine::run() {
	Clock clock;
	keyPressed = false;
	while (m_window.isOpen()) {
		Time dt = clock.restart();
		GameTimeTotal = dt;
		float dtAsSeconds = dt.asSeconds();
		updateState(); // hanldes the change of State
		init(); // initializes States
		if (Controller::isInitialized())
		{
			input(dtAsSeconds); // handles all the input
			update(dtAsSeconds); // handles updates - animation etc
			draw(); // handles drawing 
		}

	}
}


void Engine::updateState()
{
	Controller::applyChanges();
}






// TODO: changes this logic!
void Engine::initGameVariables(int indexFileToLoad) {
	/*
	string fileAddress;
	ifstream myfile;

	fileAddress = "./saves/gameFile_" + to_string(indexFileToLoad) + ".txt";
	myfile.open(fileAddress);
	*/

	mapIndex = 0;
}
