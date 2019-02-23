#pragma once
#include "pch.h"
#include <vector>
#include "Map.h"
#include <map>
#include <set>

vector<Vector2i> reconstructPath(map<pair<int, int>, pair<int, int>> cameFrom, int endPosX, int endPosY);
int ** getTotalMap(Map currentMap);
vector<Vector2i> getPath(int startPosX, int startPosY, int endPosX, int endPosY, int &energy, Map &currentMap);
vector<Vector3i> getAllAvailableTiles(int startPosX, int startPosY, int range, Map &currentMap);