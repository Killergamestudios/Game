#pragma once
#include "../../../Header Files/Windows/Theme/MainMenuWindow.h"

MainMenuWindow::MainMenuWindow(bool center, bool relativeToCamera) 
{
	this->alignment = center;
	this->relative = relativeToCamera;
	viewSize = Controller::getViewSize();
	regionDimension = Vector2f(viewSize.x*0.9f, 0);
}

MainMenuWindow::~MainMenuWindow()
{
}

void MainMenuWindow::clear()
{
	regionDimension = Vector2f(viewSize.x*0.9f,0);
}

vector<Vector2f> MainMenuWindow::renderRegion(vector<Vector2f> elements)
{
	Vector2f container = Vector2f(viewSize.x, viewSize.y*0.7f); // Set Region Container.

	float elementSeperation = (container.y - elements.size() * elements[0].y) / (elements.size() - 1); // calculate element sepearation
	
	vector<Vector2f> renderedElements;	// Array with the dimensions of the elements
	if (alignment)
		renderedElements.push_back(Vector2f(ceil((container.x - elements[0].x) / 2), ceil(viewSize.y * 0.3f + regionDimension.y)));
	else
		renderedElements.push_back(Vector2f(ceil((viewSize.x - container.x) / 2), ceil(viewSize.y * 0.3f + regionDimension.y)));
	regionDimension.x = elements[0].x; 
	regionDimension.y = elements[0].y;
	elements.erase(elements.begin());
	for (Vector2f& element : elements) {
		if (alignment)
			renderedElements.push_back(Vector2f(ceil((container.x - element.x) / 2), ceil(viewSize.y * 0.3f + regionDimension.y)));
		else
			renderedElements.push_back(Vector2f(ceil((viewSize.x - container.x) / 2), ceil(elementSeperation + regionDimension.y)));
		regionDimension.x = max(elements[0].x, regionDimension.x);
		regionDimension.y += elements[0].y;
	}

	if (relative) {
		Vector2f offset = Controller::getCameraOffset();
		for (Vector2f& rendElem : renderedElements) {
			rendElem += offset;
		}
	}
	
	return renderedElements;
}

Vector2f MainMenuWindow::getRegionDimension()
{
	return regionDimension;
}
