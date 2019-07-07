#pragma once
#include "../../../Header Files/Windows/Theme/NewWindow.h"

NewWindow::NewWindow(int alignment, bool relative) 
{
	this->alignment = alignment;
	this->relative = relative;
	regionDimension = Vector2f(0, 0);
	viewSize = Controller::getViewSize();
}

NewWindow::~NewWindow()
{
}

void NewWindow::clear()
{
	regionDimension = Vector2f(0, 0);
}

vector<Vector2f> NewWindow::renderRegion(vector<Vector2f> elements)
{
	vector<Vector2f> renderedElements;
	// first FloatRect is the background of the new window
	float xOrg = 1 / 2; // By default origin is set to center
	float yOrg = 1 / 2; //
	if (alignment != 4) {
		xOrg = (float)(alignment / 2); // if position is not center then change origin
		yOrg = (float)(alignment % 2); // 
	}

	// get the new origin based on the dimensions of the first element (background - container)
	Vector2f origin((viewSize.x - elements[0].x)*xOrg, (viewSize.y - elements[0].y)*yOrg);
	renderedElements.push_back(origin);
	viewSize.x = elements[0].x; // save dimenstion of container
	viewSize.y = elements[0].y; // 
	regionDimension.x = elements[0].x;
	elements.erase(elements.begin()); // erase the background from the list in order to have only elements to process
	float elementSeperation = (viewSize.y - elements.size() * elements[0].y) / (elements.size() + 1); // calculate element sepearation
	for (Vector2f element : elements) {
		renderedElements.push_back(Vector2f(ceil((origin.x + viewSize.x - element.x) / 2), 
			ceil(origin.y + elementSeperation + regionDimension.y)));
		
		regionDimension.y += element.y + elementSeperation;
	}

	if (relative) {
		Vector2f offset = Controller::getCameraOffset();
		for (Vector2f& rendElem : renderedElements) {
			rendElem.x += offset.x;
			rendElem.y += offset.y;
		}
	}

	return renderedElements;
}

Vector2f NewWindow::getRegionDimension()
{
	return regionDimension;
}
