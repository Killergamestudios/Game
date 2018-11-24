#include "pch.h"
#include <vector>
#include "Map.cpp"
#include <map>
#include <set>

using namespace std;

typedef pair<int, pair<int, int>> pPair;

typedef pair<int, int> Pair;


// function to reconstruct the path form getPath function
vector<Vector2i> reconstructPath(map<pair<int, int>, pair<int, int>> cameFrom, int endPosX, int endPosY) {
	vector<Vector2i> totalPath;
	totalPath.push_back(Vector2i(endPosX, endPosY));
	int x = endPosX;
	int y = endPosY;
	while (cameFrom.find(make_pair(x, y)) != cameFrom.end())
	{
		Pair next = cameFrom[make_pair(x, y)];
		x = next.first;
		y = next.second;
		totalPath.push_back(Vector2i(x, y));
	}

	return totalPath;
}

// construct totalMap using the layers provided by Map class
int ** getTotalMap(Map currentMap) {
	int ** terrainMap = currentMap.getTerrainMap();
	int ** enemyMap = currentMap.getEnemyMap();
	int ** friendlyMap = currentMap.getFriendlyMap();
	int ** miscMap = currentMap.getMiscMap();
	int width = (currentMap.getMapWidth()) / 64;
	int height = (currentMap.getMapHeight()) / 64;
	int ** map = new int*[width];

	for (int i = 0; i < width; i++)
	{
		map[i] = new int[height];
		for (int j = 0; j < height; j++)
		{
			if (enemyMap[i][j] != 0 || friendlyMap[i][j] != 0 || terrainMap[i][j] == -1) // which blocks are blocked
				map[i][j] = -1; // tile is blocked
			else
				map[i][j] = terrainMap[i][j]; // tile is not blocked
		}
	}

	return map;
}

// function that estimates the distance between two tiles (can be optimised)
int heuristicCostEstimate(int startPosX, int startPosY, int endPosX, int endPosY)
{
	return abs(startPosX - endPosX) + abs(startPosY - endPosY);
}


// function to get the optimal path between (startX, startY) and (endX, endY)
//
// Parameters:
// int startPosX, int startPosY : coordinates of starting point
// int endPosX, int endPosY : coordinates of end point
// int &energy : pass by reference the variable of the heroe's energy
// Map currentMap : currently active Map instance
//
// Returns :
// vector<Vector2i> : contains the optimal path form(startPosX, startPosY) to
//                    (endPosX, endPosY).First element is the last position of hero
//
vector<Vector2i> getPath(int startPosX, int startPosY, int endPosX, int endPosY, int &energy,Map currentMap)
{
	pPair start = make_pair(heuristicCostEstimate(startPosX, startPosY, endPosX, endPosY), make_pair(startPosX, startPosY));
	set<pPair> openSet; // tiles that are to be processed
	map<pair<int, int>, bool> closedSet; // tiles that have already been processed
	map<pair<int,int>,pair<int,int>> cameFrom; // list keeping track of the optimal path
	int ** gScore;  // the weight to get to a certain node from the start
	int ** totalMap = getTotalMap(currentMap); // map containing all the weights and blocked tiles
	int mapWidth = currentMap.getMapWidth(); // width of map array
	int mapHeight = currentMap.getMapHeight(); // height of map array

	openSet.insert(start);
	// initialize gscore
	gScore = new int *[mapWidth]; 
	for (int i = 0; i < mapWidth; i++)
	{
		gScore[i] = new int[mapHeight];
		for (int j = 0; j < mapHeight; j++)
		{
			gScore[i][j] = INT32_MAX;
		}
	}
	gScore[startPosX][startPosY] = 0; // gscore(start) = 0
	
	while (openSet.size() != 0) 
	{
		pPair p = *openSet.begin(); // pop first item from openSet (this with the least weight)
		int x = p.second.first;     //
		int y = p.second.second;    // get its coordinates
		if (x == endPosX && y == endPosY)  // check if we found the end
		{
			energy -= gScore[endPosX][endPosY];
			return reconstructPath(cameFrom,endPosX,endPosY);
		}
		openSet.erase(openSet.begin()); // erase first item from openSet (this with the least weight)
		closedSet[make_pair(x,y)] = true; // mark as evaluated to its optimal value

		// create the abjucent tiles (x+1,y) (x-1,y) (x,y+1) (x,y-1) 
		for (int i = x - 1; i <= x + 1; i+=2)
		{
			if (i < 0 || i > mapWidth - 1 || closedSet[make_pair(i, y)] == true || totalMap[i][y] == -1) // blocked or already "closed" tiles
				continue;

			int score = gScore[x][y] + totalMap[i][y]; //calculate new score = distance to parent + weight of tile

			if (gScore[i][y] == INT32_MAX) // if never visited before add it to openSet
				openSet.insert(make_pair(score + heuristicCostEstimate(i, y, endPosX, endPosY), make_pair(i, y)));
			else if (score >= gScore[i][y]) // if score is worse than the already registered, continue
				continue;
			
			// add tile to the list. Lower weight found!
			cameFrom[make_pair(i,y)] = make_pair(x,y); 
			gScore[i][y] = score;
		}

		for (int j = y - 1; j <= y + 1; j += 2)
		{
			if (j < 0 || j > mapHeight - 1 || closedSet[make_pair(x, j)] == true || totalMap[x][j] == -1) // blocked or already "closed" tiles
				continue;
			int score = gScore[x][y] + totalMap[x][j]; //calculate new score = distance to parent + weight of tile

			if (gScore[x][j] == INT32_MAX) // if never visited before add it to openSet
				openSet.insert(make_pair(score + heuristicCostEstimate(x, j, endPosX, endPosY), make_pair(x, j)));
			else if (score >= gScore[x][j]) // if score is worse than the already registered, continue
				continue;

			// add tile to the list. Lower weight found!
			cameFrom[make_pair(x, j)] = make_pair(x, y);
			gScore[x][j] = score;
		}
	}
}

// function to find all the tiles you can access given a starting point and a range 
// Parameters:
// int startPosX, int startPosY : coordinates of starting point
// int range : the total movement distance the hero can travel
// Map currentMap : currently active Map instance
//
// Returns :
// vector<Vector3i>: contains all the available tiles sorted by X value and their respective distance
//
vector<Vector3i> getAllAvailableTiles(int startPosX, int startPosY, int range, Map currentMap)
{
	pPair start = make_pair(0, make_pair(startPosX, startPosY)); //the starting point and its distance from the beginning = 0
	Pair startW = make_pair(startPosX, startPosY); // the starting point without weight
	map<pair<int, int>, bool> closedSet; // tiles that have already been processed
	vector<pPair> openSet; // tiles that are to be processed
	vector<Vector3i> finalTilesSet; // the final set of tiles to return
	set<pair<int, int>> tiles; // array keeping track of tiles. Needs to be set in order not to accept duplicates
	int mapWidth = currentMap.getMapWidth(); // width of map array
	int mapHeight = currentMap.getMapHeight(); // height of map array
	int ** energyCost;
	
	energyCost = new int *[mapWidth];
	for (int i = 0; i < mapWidth; i++)
	{
		energyCost[i] = new int[mapHeight];
		for (int j = 0; j < mapHeight; j++)
		{
			energyCost[i][j] = 0;
		}
	}


	closedSet[startW] = false;
	openSet.push_back(start);
	tiles.insert(startW);
	int ** totalMap = getTotalMap(currentMap);

	while (openSet.size() != 0)
	{
		pPair p = *openSet.begin(); // pop first item from openSet (this with the least weight)
		int x = p.second.first;  //
		int y = p.second.second; // get its coordinates
		int weight = p.first; // get the distance to this tile
		openSet.erase(openSet.begin()); // erase first item from set
		closedSet[make_pair(x, y)] = true; // mark as evaluted to its optimal value

		// create the abjucent tiles (x+1,y) (x-1,y) (x,y+1) (x,y-1) 
		for (int i = x - 1; i <= x + 1; i += 2)
		{
			// if outOfbound or blocked continue
			if (i < 0 || i > mapWidth - 1 || totalMap[i][y] == -1)
				continue;
			int newWeight = totalMap[i][y] + weight; // evaluate its distance
			if (closedSet[make_pair(i, y)] || newWeight > range) // if outOfRange ignore
				continue;
			tiles.insert(make_pair(i, y)); // insert the tile because it is in range
			
			if (energyCost[i][y] == 0 || energyCost[i][y] > newWeight)
				energyCost[i][y] = newWeight; // track energy cost
			 
			if (newWeight < range) // if we can go further than that add it to the openSet
			{
				openSet.push_back(make_pair(newWeight, make_pair(i, y)));
			}
		}

		for (int j = y - 1; j <= y + 1; j += 2)
		{
			// if outOfbound or blocked continue
			if (j < 0 || j > mapHeight - 1 || totalMap[x][j] == -1)
				continue;
			int newWeight = totalMap[x][j] + weight; // evaluate its distance
			if (closedSet[make_pair(x, j)] || newWeight > range) // if outOfRange ignore
				continue;
			tiles.insert(make_pair(x, j)); // insert the tile because it is in range

			if (energyCost[x][j] == 0 || energyCost[x][j] > newWeight) 
				energyCost[x][j] = newWeight;  // track energy cost

			if (newWeight < range) // if we can go further than that add it to the openSet
			{
				openSet.push_back(make_pair(newWeight, make_pair(x, j)));
			}

		}
	}

	// create finalTilesSet in order to return a vector and not a set
	for (Pair p : tiles)
	{
		finalTilesSet.push_back(Vector3i(p.first,p.second, energyCost[p.first][p.second]));
	}
	return finalTilesSet;
}
