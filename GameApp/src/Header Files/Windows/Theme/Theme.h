#pragma once
#include <SFML/Graphics.hpp>
#include "../../Core/Controller.h"

using namespace std;
using namespace sf;

class Theme
{
public:
	Theme();
	~Theme();
	virtual void clear() = 0;
	virtual vector<Vector2f> renderRegion(vector<Vector2f>);
	virtual Vector2f renderRegion(Vector2f);
	virtual Vector2f getRegionDimension() = 0;
};

