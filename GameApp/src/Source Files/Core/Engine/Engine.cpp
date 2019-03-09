#pragma once
#include "../../../Header Files/Core/Engine.h"
#include "../../../Header Files/Core/textureHolder.h"
#include "fstream"

Engine::Engine() {

	// get resolution from ini file. Need casting to int
	viewWidth = (float) Controller::getResolutionWidth();
	viewHeight = (float) Controller::getResolitionHeight();
	windowWidth = (float) VideoMode::getDesktopMode().width;
	windowHeight = (float) VideoMode::getDesktopMode().height;
	m_window.create(VideoMode((unsigned int)windowWidth,(unsigned int)windowHeight), "Game Name", Style::Fullscreen);
	camera.setViewport(FloatRect((windowWidth - viewWidth) / 2 / windowWidth, (windowHeight - viewHeight) / 2 / windowHeight,
									viewWidth / windowWidth, viewHeight / windowHeight));
	camera.setCenter(Vector2f(viewWidth / 2, viewHeight / 2));
	camera.setSize(Vector2f(viewWidth, viewHeight));
	m_window.setView(camera);
	m_theme = new Theme(m_window);
	tile_sprite = Sprite(TextureHolder::GetTexture("./graphics/interfaces/tileSelectorAnimated.png"));
	
}

void Engine::run() {
	Clock clock;
	m_map = new Map(m_window);
	keyPressed = false;
	m_controller.setMap(m_map);

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


void Engine::mouseControl()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// left click...
	}
	// get global mouse position
	sf::Vector2i position = sf::Mouse::getPosition(m_window);

	//Calculating the local position of the mouse based on the view Size and the Camera Position.
	int localX = position.x - windowWidth / 2 + viewWidth / 2 + camera.getCenter().x- camera.getSize().x / 2;
	int localY = position.y -windowHeight/2 +viewHeight/2 + camera.getCenter().y - camera.getSize().y / 2;
	tile_sprite.setPosition(localX - localX% 64,localY - localY% 64); //Setting the position to draw the target selector
	
	sf::Vector2i localPos(localX / 64, localY / 64); // Finding the mouse position in the Map 2D Arrays.
	if (Controller::getMap()->getFriendlyinPosition(localPos) > 0)
	{
		tile_sprite.setTextureRect(sf::IntRect(0, 64, 64, 64)); // If friendly is on a tile, set the color of the target selector to yellow.
	}
	else if (Controller::getMap()->getEnemyinPosition(localPos) > 0)
	{
		tile_sprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); //If enemy is on a tile, set the color of the target selector to red.
	}
	else
	{
		tile_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); //If there is nothing set the color of the target selector to blue.
	}
	
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
