#pragma once
#include "Theme.h"

class Background :public Theme
{
public:
	Background(bool, bool);
	~Background();
	void clear() override;
	Vector2f renderRegion(Vector2f) override;
	Vector2f getRegionDimension() override;

	bool alignment, relative;
	Vector2f viewSize, regionDimension;
};