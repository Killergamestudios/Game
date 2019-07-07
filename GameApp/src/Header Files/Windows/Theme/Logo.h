#pragma once
#include "Theme.h"

class Logo :public Theme
{
public:
	Logo(bool);
	~Logo();
	void clear() override;
	Vector2f renderRegion(Vector2f) override;
	Vector2f getRegionDimension() override;

	bool alignment, relative;
	Vector2f viewSize, regionDimension;
};

