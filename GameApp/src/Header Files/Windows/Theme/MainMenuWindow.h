#pragma once
#include "Theme.h"

class MainMenuWindow :public Theme
{
public:
	MainMenuWindow(bool, bool);
	~MainMenuWindow();
	void clear() override;
	vector<Vector2f> renderRegion(vector<Vector2f>) override;
	Vector2f getRegionDimension() override;

	bool alignment, relative;
	Vector2f viewSize, regionDimension;
};