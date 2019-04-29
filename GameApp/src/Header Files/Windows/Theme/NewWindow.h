#pragma once
#include "Theme.h"

class NewWindow:public Theme
{
public:
	NewWindow(int, bool);
	~NewWindow();
	void clear() override;
	vector<Vector2f> renderRegion(vector<Vector2f>) override;
	Vector2f getRegionDimension() override;

	int alignment;
	bool relative;
	Vector2f viewSize, regionDimension;
};