#pragma once
#include "textureHolder.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "MainMenu.h"


using namespace sf;
enum State{Booting,Playing, Loading, InMenu, Incutscene};
//enum InputState {}; // needs work later
class Engine {
private:
	const int tyle_size = 64;
	const int verts_in_quad = 4;
	int mapIndex;
	RenderWindow m_window;
	Time GameTimeTotal;
	State m_state;
	TextureHolder m_textureHolder;
	Map *m_map;
	MainMenu *mainmenu;
	map<string, string> controlUnit;

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
	void updateState();

	void clearControlUnit(bool); // clears controlUnit false = soft flush, true = hard flush
	void cameraUpdate(int direction); // handles movement of camera

public:
	Engine();
	void run();
};
