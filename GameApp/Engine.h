#pragma once
#include "textureHolder.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "GameMenu.h"
#include "MainMenu.h"
#include "BootMenu.h"
#include "InGameMainMenu.h"
#include "object.h"
#include "Controller.h"
#include "Theme.h"

using namespace sf;
//enum State{Booting,Playing, Loading, InMenu, Incutscene};
//enum InputState {}; // needs work later
class Engine {
private:
	const int tyle_size = 64;
	const int verts_in_quad = 4;
	int mapIndex;
	RenderWindow m_window;
	Time GameTimeTotal;
	//State m_state;
	TextureHolder m_textureHolder;
	Controller m_controller;
	Map *m_map;
	GameMenu *mainmenu;
	Theme *m_theme;
	//map<string, string> controlUnit;

	// camera variables
	View camera;
	const float CAMERA_SPEED = 64.0f;
	const float CAMERA_UPDATE_SPEED = 0.1f;
	//--------------------------

	// variables for keyPressed events (lock, override)
	bool keyPressed; // boolean flag to indicate that a key is pressed
	float overrideKeyPressed;  // float variable for time keeping while key is pressed
	const float CHANGE_SELECTION_SPEED = 0.5f; // Change speed for faster or slower option transition
	// -------------------------------------------------

	// game constancts
	float windowWidth;
	float windowHeight;
	float mapWidth;
	float mapHeight;
	// --------------------------------------------------

	void initGameVariables(int indexFileToLoad);

	void input(float dtAsSeconds);
	void update(float dtAsSeconds);
	void draw();
	void init();
	void updateState();

	void cameraUpdate(int direction); // handles movement of camera
	void cameraReset(); // resets camera. Useful for state transitions

	//CharacterObject *SpawnCharacter(Vector2i position, Map *map,string savefilename,string Name,string Class);
	//vector<CharacterObject*> *loadParty(Map *map, string savefilename, vector<Vector3i> pos);
	//CharacterObject *Warrior;//temp
	//CharacterObject *mage;
	vector<CharacterObject> party;
public:
	Engine();
	void run();
};
