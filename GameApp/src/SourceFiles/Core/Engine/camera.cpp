#include "pch.h"
#include "Engine.h"


void Engine::cameraUpdate(int direction)
{	
	camera.move(Vector2f((direction/2)*CAMERA_SPEED, (direction%2)*CAMERA_SPEED)); // movement of camera

	if (camera.getCenter().x < camera.getSize().x / 2) // left overflow
	{
		camera.setCenter(camera.getSize().x / 2, camera.getCenter().y);
	}
	else if (camera.getCenter().y < camera.getSize().y / 2) // up overflow
	{
		camera.setCenter(camera.getCenter().x, camera.getSize().y / 2);
	}
	else if (camera.getCenter().x > mapWidth - (camera.getSize().x / 2)) // right overflow
	{
		camera.setCenter(mapWidth - (camera.getSize().x / 2), camera.getCenter().y);
	}
	else if (camera.getCenter().y > mapHeight - (camera.getSize().y / 2)) // down overflow
	{
		camera.setCenter(camera.getCenter().x, mapHeight - (camera.getSize().y / 2));
	}
}

void Engine::cameraReset() {
	camera.setCenter(viewWidth/2,viewHeight/2);
}