#pragma once
#include <vector>
#include "Map.h"
#include <map>
#include <set>


// function to reconstruct the path form getPath function
vector<Vector2i> reconstructPath(map<pair<int, int>, pair<int, int>> cameFrom, int endPosX, int endPosY);

// construct totalMap using the layers provided by Map class
int ** getTotalMap(Map currentMap);

// function to get the optimal path between (startX, startY) and (endX, endY)
//
// Parameters:
// int startPosX, int startPosY : coordinates of starting point
// int endPosX, int endPosY : coordinates of end point
// int &energy : pass by reference the variable of the heroe's energy
// Map currentMap : currently active Map instance
//
// Returns :
// vector<Vector2i> : contains the optimal path from(startPosX, startPosY) to
//                    (endPosX, endPosY).First element is the last position of hero
//
vector<Vector2i> getPath(int startPosX, int startPosY, int endPosX, int endPosY, int &energy, Map &currentMap);

// function to find all the tiles you can access given a starting point and a range 
// Parameters:
// int startPosX, int startPosY : coordinates of starting point
// int range : the total movement distance the hero can travel
// Map currentMap : currently active Map instance
//
// Returns :
// vector<Vector3i>: contains all the available tiles sorted by X value and their respective distance
//
vector<Vector3i> getAllAvailableTiles(int startPosX, int startPosY, int range, Map &currentMap);

// function to find all the tiles you can access if you move only on a straight line
// Parameters:
// int startPosX, int startPosY : coordinates of starting point
// int range : the total movement distance the hero can travel
// Map currentMap : currently active Map instance
//
// Returns :
// vector<Vector3i>: contains all the available tiles sorted by X value and their respective distance
//
vector<Vector3i> getStraightPath(int startPosX, int startPosY, int range, Map &currentMap);