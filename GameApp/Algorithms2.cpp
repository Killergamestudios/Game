#include "pch.h"
#include <vector>
#include "Map.cpp"
#include <map>
#include <set>

using namespace std;

typedef pair<int, pair<int, int>> pPair;

typedef pair<int, int> Pair;

vector<pair<int, int>> reconstructPath(map<pair<int, int>, pair<int, int>> cameFrom, int endPosX, int endPosY) {
	vector<pair<int, int>> totalPath;
	totalPath.push_back(make_pair(endPosX, endPosY));
	int x = endPosX;
	int y = endPosY;
	while (cameFrom.find(make_pair(x, y)) != cameFrom.end())
	{
		Pair next = cameFrom[make_pair(x, y)];
		x = next.first;
		y = next.second;
		totalPath.push_back(make_pair(x, y));
	}

	return totalPath;
}

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
int heuristicCostEstimate(int startPosX, int startPosY, int endPosX, int endPosY)
{
	return abs(startPosX - endPosX) + abs(startPosY - endPosY);
}

vector<pair<int, int>> getPath(int startPosX, int startPosY, int endPosX, int endPosY, Map currentMap) 
{
	pPair start = make_pair(heuristicCostEstimate(startPosX, startPosY, endPosX, endPosY), make_pair(startPosX, startPosY));
	set<pPair> openSet;
	openSet.insert(start);
	map<pair<int, int>, bool> closedSet;
	map<pair<int,int>,pair<int,int>> cameFrom;
	int ** gScore;
	gScore = new int *[currentMap.getMapWidth()];
	for (int i = 0; i < currentMap.getMapWidth(); i++)
	{
		gScore[i] = new int[currentMap.getMapHeight()];
		for (int j = 0; j < currentMap.getMapHeight(); j++)
		{
			gScore[i][j] = INT32_MAX;
		}
	}
	gScore[startPosX][startPosY] = 0;
	set<pPair> fScore;
	fScore.insert(start);
	
	int ** totalMap = getTotalMap(currentMap);
	
	while (openSet.size() != 0) 
	{
		pPair p = *openSet.begin();
		int x = p.second.first;
		int y = p.second.second;
		if (x == endPosX && y == endPosY) {
			return reconstructPath(cameFrom,endPosX,endPosY);
		}
		openSet.erase(openSet.begin());
		closedSet[make_pair(x,y)] = true;

		for (int i = x - 1; i <= x + 1; i+=2)
		{
			if (closedSet[make_pair(i, y)] == true)
				continue;
			int score = gScore[x][y] + totalMap[i][y];

			if (gScore[i][y] == INT32_MAX)
				openSet.insert(make_pair(score + heuristicCostEstimate(i, y, endPosX, endPosY), make_pair(i, y)));
			else if (score >= gScore[i][y])
				continue;
			
			cameFrom[make_pair(i,y)] = make_pair(x,y);
			gScore[i][y] = score;
			fScore.insert(make_pair(score + heuristicCostEstimate(i, y, endPosX, endPosY), make_pair(i, y)));
		}

		for (int j = y - 1; j <= y + 1; j += 2)
		{
			if (closedSet[make_pair(x, j)] == true)
				continue;
			int score = gScore[x][y] + totalMap[x][j];

			if (gScore[x][j] == INT32_MAX)
				openSet.insert(make_pair(score + heuristicCostEstimate(x, j, endPosX, endPosY), make_pair(x, j)));
			else if (score >= gScore[x][j])
				continue;

			cameFrom[make_pair(x, j)] = make_pair(x, y);
			gScore[x][j] = score;
			fScore.insert(make_pair(score + heuristicCostEstimate(x, j, endPosX, endPosY), make_pair(x, j)));
		}

	}
}
