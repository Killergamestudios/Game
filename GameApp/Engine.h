#pragma once
#include "textureHolder.h";


#include <SFML/Graphics.hpp>

using namespace sf;
enum State{Playing, Loading, InMenu, Incutscene};
//enum InputState {}; // needs work later
class Engine {
private:
	const int tyle_size = 64;
	const int verts_in_quad = 4;
	RenderWindow m_window;
	Time GameTimeTotal;
	State m_state;
	TextureHolder m_textureHolder;


	void input();
	void update(float dtAsSeconds);
	void draw();
public:
	Engine();
	void run();
};
