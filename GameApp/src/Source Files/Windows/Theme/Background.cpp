#pragma once
#include "../../../Header Files/Windows/Theme/Background.h"

Background::Background(bool center, bool relativeToCamera)
{
	this->alignment = center;
	this->relative = relativeToCamera;
	viewSize = Controller::getViewSize();
	regionDimension = Vector2f(0, 0);
}

Background::~Background()
{
	
}

void Background::clear()
{
	regionDimension = Vector2f(0,0);
}

Vector2f Background::renderRegion(Vector2f background)
{
	Vector2f offset(0,0);
	regionDimension = viewSize;
	if (relative) {
		offset = Controller::getCameraOffset();
	}
	if (alignment) {
		return Vector2f(ceil(offset.x + viewSize.x / 2), ceil(offset.y + viewSize.y / 2));
	}
	else {
		return Vector2f(ceil(offset.x + background.x / 2), ceil(offset.y + background.y / 2));
	}
	cout << "Incorrect Alignment Parameter" << endl;
}

Vector2f Background::getRegionDimension()
{
	return regionDimension;
}
