#pragma once
#include "textureHolder.h"
#include <SFML/Graphics.hpp>

using namespace sf;
class Map
{
public:
	Map( RenderWindow &window); //TextureHolder &textures);
	~Map();
	void init();
	void load(int mapIndex); //Loads the information in the object.
	void draw(); //Draws the Map
	


private:
	int width, height; // Store map size (width and height)
	 RenderWindow *m_window;
	//TextureHolder *m_textureHolder;
	//Texture m_texture;
	Sprite m_sprite;
	string backgroundImageAddress;
	int **m_terrainProperties; // Stores data about properties of different tiles based on Terrain.
	int **m_enemyCharacters; // Stores data about Enemy Characters
	int **m_friendlyCharacters; // Stores data about Friendly characters
	int **m_misc;   //Stores data about position of misc objects around the map. 
};

