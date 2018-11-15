#include "pch.h"
#include "Map.h"
#include "fstream"
#include <iostream>

using namespace std;

Map::Map( RenderWindow &window) //TextureHolder &textures)
{
	m_window = &window;
	//m_textureHolder = &textures;

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
	const int TILE_SIZE = 64;
	
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

		int** dummy; // Creates dummy array to prevent code repeticion
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
				if (lineReader[x] >= 'a'&& lineReader[x] <= 'z')
				{
					dummy[x][y] = (int)(lineReader[x] - 'a' + 10);
				}
				else
				{
					dummy[x][y] = (int)(lineReader[x]);
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
	return width * 64;
}

int Map::getMapHeight()
{
	return height * 64;
}
