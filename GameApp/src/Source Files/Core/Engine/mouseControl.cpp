#pragma once
#include "../../../Header Files/Core/Engine.h"

sf::Vector2i Engine::mouseControl()
{
	
	//Mouse control should be adapted to work differently depending on the state of the game. Or if an in-game menu is open it should affect the menu or not work at all.
	//Should also be able to use it for selecting where to move. It might prove useful to make this function return a value. Either return an int Value depending on the type of object it traces below the mouse,
	//or it could be returning the coordinates within the map arrays.

	int tileContent = 0; // 0 For Empty, 1 for Friendly in Tile, 2 for Enemy in Tile, 3 for Misc in tile.


	// get global mouse position
	sf::Vector2i position = sf::Mouse::getPosition(m_window);

	//Calculating the local position of the mouse based on the view Size and the Camera Position.
	int localX = int(position.x - windowWidth / 2 + viewWidth / 2 + camera.getCenter().x - camera.getSize().x / 2);
	int localY = int(position.y - windowHeight / 2 + viewHeight / 2 + camera.getCenter().y - camera.getSize().y / 2);
	tile_sprite.setPosition(float(localX - localX % TILE_SIZE), float(localY - localY % TILE_SIZE)); //Setting the position to draw the target selector

	sf::Vector2i localPos(localX / TILE_SIZE, localY / TILE_SIZE); // Finding the mouse position in the Map 2D Arrays.

	
	/*
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// left click...
		if (tileContent == 1)
		{
			//Control the character through in-game menu, disable mouseControl.
		}
		else if (tileContent == 2)
		{
			//Show up information about the target 
		}
	}
	*/
	return localPos; //After the value is returned make sure it is within the bounds of the map Arrays.
}