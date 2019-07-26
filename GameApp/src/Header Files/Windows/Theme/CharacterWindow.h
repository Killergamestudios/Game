#pragma once
#include "Theme.h"

using namespace sf;

class CharacterWindow: public Theme
{
public:
	CharacterWindow(int, bool, bool,bool);
	~CharacterWindow();
	void clear();
	void renderRegion();
	Vector2f setBackground(Vector2f, Vector2f);
	void add(Vector2f&,Vector2f&);
	void add(vector<Vector2f>, vector<Vector2f>);
	vector<Vector2f> getButtonsPositions();
	vector<Vector2f> getDiscriptionPositions();
	Vector2f getDiscriptionPositions(int index);
	Vector2f getRegionDimension();


private:
	int windowAlignmemnt;
	bool buttonsCenter, descriptionCenter, rendered, background;
	Vector2f viewSize, container, padding, origin, regionDimension, offset, backgroundPos;
	vector<Vector2f> buttons, descriptions;
	vector<Vector2f> buttonsPos, descriptionsPos;
};