#pragma once
#include "../../../Header Files/Core/Engine.h"

void Engine::mouseAnimation(float &totalTimePassed, int &animState, sf::Vector2i localPos)
{

	float animationSpeed = 0.1f; // Animation speed
	if (totalTimePassed > animationSpeed) //Animation
	{
		totalTimePassed = 0;
		animState = (animState + TILE_SIZE) % 1024; //Has 16 frames of 64 pixel.

	}

	//If the localPos is beyond the size of the data arrays of the map, don't try accessing the data tables.
	if (Controller::getMap()->getMapWidth() / TILE_SIZE <= localPos.x || Controller::getMap()->getMapHeight() / TILE_SIZE <= localPos.y || localPos.x < 0 || localPos.y < 0)
	{
		tile_sprite.setTextureRect(sf::IntRect(animState, 0, TILE_SIZE, TILE_SIZE)); //Out of bounds. Set it to blue just for no reason.
	}
	else if (Controller::getMap()->getFriendlyinPosition(localPos) > 0)
	{
		tile_sprite.setTextureRect(sf::IntRect(animState, TILE_SIZE, TILE_SIZE, TILE_SIZE)); // If friendly is on a tile, set the color of the target selector to yellow.
	}
	else if (Controller::getMap()->getEnemyinPosition(localPos) > 0)
	{
		tile_sprite.setTextureRect(sf::IntRect(animState, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE)); //If enemy is on a tile, set the color of the target selector to red.
	}
	else
	{
		tile_sprite.setTextureRect(sf::IntRect(animState, 0, TILE_SIZE, TILE_SIZE)); //If there is nothing set the color of the target selector to blue.
	}
}


