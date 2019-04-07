#pragma once
#include "textureHolder.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "../Windows/MainMenu.h"
#include "../Windows/BootMenu.h"
#include "../Windows/InGameMainMenu.h"
#include "../Objects/object.h"
#include "Controller.h"
#include "../Windows/Gui/Theme.h"
#include "../../Header Files/Core/InputCotroller.h"

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
	InputController m_InputController;
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

	bool MousePressed;

	// game constancts
	float viewWidth;
	float viewHeight;
	float mapWidth;
	float mapHeight;
	float windowWidth;
	float windowHeight;
	// --------------------------------------------------

	void initGameVariables(int indexFileToLoad);

	void input(float dtAsSeconds);
	void update(float dtAsSeconds);
	void draw();
	void init();
	void updateState();

	sf::Vector2i mouseControl(float &totaltimepassed,int &animState);

	void cameraUpdate(int direction); // handles movement of camera
	void cameraReset(); // resets camera. Useful for state transitions

	//CharacterObject *SpawnCharacter(Vector2i position, Map *map,string savefilename,string Name,string Class);
	//vector<CharacterObject*> *loadParty(Map *map, string savefilename, vector<Vector3i> pos);
	//CharacterObject *Warrior;//temp
	//CharacterObject *mage;

	Sprite tile_sprite;
	vector<CharacterObject> party;



	vector <Sprite> Highlighted_Tyles;// the tyles that get HighLighted when we select a character

	float mouseTimePass;
	int animState;

public:
	Engine();
	void run();
};
