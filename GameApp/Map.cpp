#include "pch.h"
#include "Map.h"
#include "fstream"


Map::Map(const RenderWindow &window, TextureHolder &textures)
{
	m_window = &window;
	m_textureHolder = &textures;

}


Map::~Map()
{
}

void Map::init()
{
	if (m_terrainProperties)
	{
		for (int i = 0; i < width; i++)
		{
			if (m_terrainProperties[i] != NULL)
			{
				delete m_terrainProperties[i];
			}
		}
		delete m_terrainProperties;
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
	string objToCreate;

	init(); //Initialises the arrays, emptying them up and creating them again.

	//LOOP INITIATES!!!
	for (int layerIndex = 0; layerIndex <= 3; layerIndex++)
	{
		mapAddress = "mapText_" + to_string(mapIndex) + "_L-" + to_string(layerIndex) + ".txt"; // Building the Address of the map text file to fetch.
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

		switch (layerIndex)
		{
		case 0:
			m_terrainProperties = dummy;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}
	}
}

void Map::draw()
{
}
