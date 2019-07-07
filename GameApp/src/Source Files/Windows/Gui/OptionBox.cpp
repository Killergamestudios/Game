#pragma once
#include "../../../Header Files/Windows/Gui/OptionBox.h"


OptionBox::OptionBox(RenderWindow *window, Text label, Font font, Theme *theme,
	int currentValue, vector<pair<string,string>> options)
	:GuiElement(window, label, font, theme)
{
	this->currentValue = (float)currentValue;
	this->options = options;
	init();
}


OptionBox::~OptionBox()
{
}

void OptionBox::init()
{
	VIEW_WIDTH = max(theme->getRegionDimension().x, 670.f);
	padding = Vector2f(VIEW_WIDTH / 20, VIEW_HEIGHT / 20);
	dimensions = Vector2f(VIEW_WIDTH, (float)label.getCharacterSize() + padding.y);
	selected.setString(options[(int)currentValue].first + " x " + options[(int)currentValue].second);
	selected.setCharacterSize(30);
	selected.setFont(font);
}

void OptionBox::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(selected, states);
	target.draw(label, states);
}

void OptionBox::update(int direction)
{
	if (currentValue + direction < options.size() && currentValue + direction >= 0)
	{
		currentValue = (float) currentValue + direction;
		selected.setString(options[(int)currentValue].first + " x " + options[(int)currentValue].second);
		float width = selected.getLocalBounds().width;
		selected.setPosition(Vector2f(VIEW_WIDTH + offset.x - width, offset.y));
	}
}

void OptionBox::setPosition(Vector2f newPositions)
{
	offset = newPositions;

	label.setPosition(Vector2f(offset.x, offset.y));
	float width = selected.getLocalBounds().width;
	selected.setPosition(Vector2f(VIEW_WIDTH + offset.x - width, offset.y));
}

Vector2f OptionBox::getDimensions()
{
	return dimensions;
}

float OptionBox::getValue() {
	return currentValue;
}

void OptionBox::setSelected()
{
	label.setFillColor(Color::Red);
}

void OptionBox::unSelect()
{
	label.setFillColor(Color::White);
}