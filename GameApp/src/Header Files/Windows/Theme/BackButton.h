#pragma once
#include "Theme.h"

class BackButton :public Theme
{
public:
	BackButton(bool, bool);
	~BackButton();
	void clear() override;
	Vector2f renderRegion(Vector2f) override;
	Vector2f getRegionDimension() override;

	bool alignment, relative;
	Vector2f viewSize, regionDimension;
};