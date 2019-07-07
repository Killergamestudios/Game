#pragma once
#include "../../../Header Files/Windows/Theme/BackButton.h"

BackButton::BackButton(bool center, bool relativeToCamera)
{
	this->alignment = center;
	this->relative = relativeToCamera;
	regionDimension = Vector2f(0, 0);
	viewSize = Controller::getViewSize();
}

BackButton::~BackButton()
{
}

void BackButton::clear()
{
	regionDimension = Vector2f(0, 0);
}

Vector2f BackButton::renderRegion(Vector2f element)
{
	Vector2f container(viewSize.x * 0.95f, viewSize.y * 0.95f);
	regionDimension.x = viewSize.x;
	regionDimension.y = element.y;
	Vector2f offset(0,0);
	if (relative) {
		offset = Controller::getCameraOffset();
	}
	if (alignment) {
		return (Vector2f(ceil((viewSize.x - element.x) / 2.f), ceil((viewSize.y + container.y) / 2.f - element.y)) + offset);
	}
	return (Vector2f(ceil((viewSize.x + container.x) / 2.f - element.x), ceil((viewSize.y + container.y) / 2.f - element.y)) + offset);
	
}

vector<Vector2f> BackButton::renderRegion(vector<Vector2f> elements)
{
	return vector<Vector2f>{renderRegion(elements[0])};
}

Vector2f BackButton::getRegionDimension()
{
	return Vector2f();
}
