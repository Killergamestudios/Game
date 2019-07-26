#pragma once
#include "..\..\..\Header Files\Windows\Theme\CharacterWindow.h"
using namespace sf;

CharacterWindow::CharacterWindow(int windowPosition, bool buttonsCenter, bool descriptionCenter, bool relativeToCamera)
{
	windowAlignmemnt = windowPosition;
	this->buttonsCenter = buttonsCenter;
	this->descriptionCenter = descriptionCenter;
	viewSize = Controller::getViewSize();
	regionDimension = Vector2f(0, 0);
	rendered = false;
	background = false;
	offset = Vector2f(0.f, 0.f);
	if (relativeToCamera)
		offset = Controller::getCameraOffset();
}

CharacterWindow::~CharacterWindow()
{
	buttons.clear();
	descriptions.clear();
	buttonsPos.clear();
	descriptionsPos.clear();
}

void CharacterWindow::clear()
{
	buttons.clear();
	descriptions.clear();
	buttonsPos.clear();
	descriptionsPos.clear();
	regionDimension *= 0.f;
	origin *= 0.f;
	rendered = false;
	background = false;
}

void CharacterWindow::renderRegion()
{
	rendered = true;
	const float SEPERATOR = 0.4f;
	regionDimension.x = SEPERATOR * container.x;
	float elementSeperation = (container.y - buttons.size() * buttons[0].y) / (buttons.size() + 1); // calculate buttons sepearation
	for (Vector2f& button : buttons) {
		buttonsPos.push_back((Vector2f(ceil(backgroundPos.x + (container.x*SEPERATOR - button.x) / 2),
			ceil(backgroundPos.y + elementSeperation + regionDimension.y))));
		regionDimension.y += button.y + elementSeperation;
	}

	for (Vector2f& description : descriptions) {
		descriptionsPos.push_back(Vector2f(ceil(backgroundPos.x + container.x*SEPERATOR + (container.x*(1-SEPERATOR) - description.x) / 2),
			ceil(backgroundPos.y)));
	}
}

Vector2f CharacterWindow::setBackground(Vector2f background, Vector2f padding)
{
	this->background = true;
	origin = Vector2f(0.5f, 0.5f);
	if (windowAlignmemnt != 4) {
		origin.x = (float)(windowAlignmemnt / 2); // if position is not center then change origin
		origin.y = (float)(windowAlignmemnt % 2); // 
	}
	this->padding = padding;
	container = background - padding;
	backgroundPos = Vector2f((viewSize.x - container.x) * origin.x, (viewSize.y - container.y) * origin.y) + offset;
	return Vector2f((viewSize.x - background.x) * origin.x, (viewSize.y - background.y) * origin.y) + offset;
}

void CharacterWindow::add(Vector2f &button, Vector2f &description)
{
	buttons.push_back(button);
	descriptions.push_back(description);
}

void CharacterWindow::add(vector<Vector2f> btns, vector<Vector2f> descrs)
{
	buttons.insert(buttons.end(), btns.begin(), btns.end());
	descriptions.insert(descriptions.end(), descrs.begin(), descrs.end());
}

vector<Vector2f> CharacterWindow::getButtonsPositions()
{
	if (!rendered) {
		cout << "Not Rendered!!" << endl;
		return vector<Vector2f>();
	}
	return buttonsPos;
}

vector<Vector2f> CharacterWindow::getDiscriptionPositions()
{
	if (!rendered) {
		cout << "Not Rendered!!" << endl;
		return vector<Vector2f>();
	}
	return descriptionsPos;
}

Vector2f CharacterWindow::getDiscriptionPositions(int index)
{
	if (!rendered) {
		cout << "Not Rendered!!" << endl;
		return Vector2f();
	}
	return descriptionsPos[index];
}

Vector2f CharacterWindow::getRegionDimension()
{
	return regionDimension;
}
