#pragma once
#include "pch.h"
#include "Engine.h"
#include "textureHolder.h"
#include "fstream"
#include "IniReader.h"
#include "IniWriter.h"
#include <Windows.h>

Engine::Engine() {
	IniReader iniReader("D:\\Projects\\GameApp\\GameApp\\options.ini");
	string resolutionWidth = iniReader.ReadVar("Display", "width", "");
	string resolutionHeight = iniReader.ReadVar("Display", "height", "");
	
	windowWidth = stoi(resolutionWidth); 
	windowHeight = stoi(resolutionHeight); 
	m_window.create(VideoMode((unsigned int)windowWidth,(unsigned int)windowHeight), "Game Name", Style::Fullscreen);
	camera.setCenter(Vector2f(windowWidth/2, windowHeight/2));
	camera.setSize(Vector2f(windowWidth, windowHeight));
	m_window.setView(camera);
}

void Engine::run() {
	Clock clock;
	m_map = new Map(m_window);
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
