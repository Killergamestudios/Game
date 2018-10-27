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


	void input();
	void update(float dtAsSeconds);
	void draw();



public:
	Engine();
	void run();
};
