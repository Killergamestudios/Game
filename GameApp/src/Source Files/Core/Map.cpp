#pragma once
#include "../../Header Files/Core/Map.h"
#include "fstream"
#include <iostream>
#include <sstream>

using namespace std;

Map::Map( RenderWindow &window)
{
	m_window = &window;

}


Map::~Map()
{
}

void Map::init()
{
	//Deletes m_terrainProperties if it is not empty.
	if (m_terrainProperties)
	{
		for (int i = 0; i < width; i++)
		{
			if (m_terrainProperties[i] != NULL)
			{
				delete m_terrainProperties[i];
				delete m_enemyCharacters[i];
				delete m_friendlyCharacters[i];
				delete m_misc[i];
			}
		}
		delete m_terrainProperties;
		delete m_enemyCharacters;
		delete m_friendlyCharacters;
		delete m_misc;


	}
	

	// Need to initiate the other three arrays found in the header file privates , enemy characters, characaters, misc/
	height = 0;
	width = 0;
}

void Map::load(int mapIndex)
{
	ifstream myfile;
	string mapAddress;
	string lineReader;
	int y; // Current Row that is being checked.
	//int printX; // X coordinate to print.
	//int printY; // Y coordinate to print.
	
	
	backgroundImageAddress = "./graphics/maps/backgrounds/map_" + to_string(mapIndex) +".png";
	init(); //Initialises the arrays, emptying them up and creating them again.
	//LOOP INITIATES!!!
	for (int layerIndex = 0; layerIndex <= 3; layerIndex++)
	{
		mapAddress = "./graphics/maps/texts/mapText_" + to_string(mapIndex) + "_L-" + to_string(layerIndex) + ".txt"; // Building the Address of the map text file to fetch.
		myfile.open(mapAddress);

		if (layerIndex == 0)
		{
			while (getline(myfile, lineReader))
			{
				height++; //Calculates Height;
			}
			width = lineReader.length(); // Gets Width of ONCE

			// Go back to the start of the file
			myfile.clear();
			myfile.seekg(0, ios::beg);
		}

		 // Creates dummy array to prevent code repeticion
		int** dummy;
		dummy = new int*[width];
		for (int i = 0; i < width; i++) {
			dummy[i] = new int[height];
		}
		y = 0; // First Column to Check is the 0.
		while (getline(myfile, lineReader))
		{
			for (int x = 0; x < width; x++) // x goes from colum to column starting from 0 and reaching the final column.
			{
				//lineReader[x] -> The Symbol of the Item in Column- x and Row - y.
				if (lineReader[x] == 'z')
				{
					dummy[x][y] = -1;
				}
				else if (lineReader[x] >= 'a'&& lineReader[x] < 'z')
				{
					dummy[x][y] = (int)(lineReader[x] - 'a' + 10);
				}
				else
				{
					dummy[x][y] = (int)(lineReader[x]) - 48;
				}
			}
			y++; // Going to the next Row.
		}
		//Copying Dummy to the appropriate array.
		switch (layerIndex)
		{
		case 0:
			m_terrainProperties = dummy;
			break;
		case 1:
			m_enemyCharacters = dummy;
			break;
		case 2:
			m_friendlyCharacters = dummy;
			break;
		case 3:
			m_misc = dummy;
			break;
		}
		myfile.close();
	}

	m_sprite = Sprite(TextureHolder::GetTexture(backgroundImageAddress));
	m_sprite.setPosition(0, 0);
}

void Map::draw()
{
	m_window->draw(m_sprite);
}

int Map::getMapWidth()
{
	return width * TILE_SIZE;
}

int Map::getMapHeight()
{
	return height * TILE_SIZE;
}

int Map::getTerainPropertiesinPosition(Vector2i position)
{
	return m_terrainProperties[position.x][position.y];
}

int Map::getEnemyinPosition(Vector2i position)
{
	
	return m_enemyCharacters[position.x][position.y];
}

int Map::getFriendlyinPosition(Vector2i position)
{
	return m_friendlyCharacters[position.x][position.y];
}

int Map::getMiscinPosition(Vector2i position)
{
	return m_misc[position.x][position.y];
}

void Map::swapPosition(string maptype, Vector2i Startingpos, Vector2i Destination)
{
	int temp;
	cout << Startingpos.x << Startingpos.y << endl;
	cout << Destination.x << Destination.y << endl;
	if (maptype == "friendly") {
		temp = m_friendlyCharacters[Startingpos.x][Startingpos.y];
		m_friendlyCharacters[Startingpos.x][Startingpos.y] = m_friendlyCharacters[Destination.x][Destination.y];
		m_friendlyCharacters[Destination.x][Destination.y] = temp;
	}
	else if (maptype == "enemy") {
		temp = m_enemyCharacters[Startingpos.x][Startingpos.y];
		m_enemyCharacters[Startingpos.x][Startingpos.y] = m_enemyCharacters[Destination.x][Destination.y];
		m_enemyCharacters[Destination.x][Destination.y] = temp;
	}
}

CharacterObject Map::getenemy(Vector2i position)
{
	for (unsigned int i = 0; i < m_enemys.size(); i++) {
		if (position.x == m_enemys[i].getMyPosition().x &&position.y == m_enemys[i].getMyPosition().y) return m_enemys[i];
	}
	throw std::exception("Invalid Search");
}

int ** Map::getTerrainMap() 
{
	return m_terrainProperties;
}

int ** Map::getEnemyMap()
{
	return m_enemyCharacters;
}

int ** Map::getFriendlyMap()
{
	return m_friendlyCharacters;
}

int ** Map::getMiscMap()
{
	return m_misc;
}