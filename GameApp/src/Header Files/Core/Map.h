#pragma once
#include "textureHolder.h"
#include <SFML/Graphics.hpp>
#include "../Objects/object.h"
#include "Controller.h"

class CharacterObject;
using namespace sf;
class Map
{
public:
	Map( RenderWindow &window); //TextureHolder &textures);
	~Map();
	void init();
	void load(int mapIndex); //Loads the information in the object.
	void draw(); //Draws the Map
	int getMapWidth();
	int getMapHeight();
	int ** getTerrainMap();
	int ** getEnemyMap();
	int ** getFriendlyMap();
	int ** getMiscMap();
	int getTerainPropertiesinPosition(Vector2i position);
	int getEnemyinPosition(Vector2i position);
	int getFriendlyinPosition(Vector2i position);
	int getMiscinPosition(Vector2i position);
	void swapPosition(string maptype, Vector2i Startingpos, Vector2i Destination);
	


	CharacterObject getenemy(Vector2i);
	CharacterObject *SpawnCharacter(Vector2i position,string savefilename, string Name, string Class);
	void loadParty(Map *map,string savefilename);
	
	vector<CharacterObject> &getparty();
	vector<CharacterObject> &getenemys();

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

	std::vector<CharacterObject> m_enemys;
	std::vector<CharacterObject> party;

};

