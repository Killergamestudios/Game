#pragma once
#include "../../../Header Files/Windows/Gui/ValueBar.h"

ValueBar::ValueBar(RenderWindow *window, Text label, Font font, Theme::Regions region,
	float currentValue,float max, float min, float step)
	:GuiElement(window,label,font,region)
{
	this->currentValue = currentValue;
	this->maxValue = max;
	this->minValue = min;
	this->step = step;
	init();
}


ValueBar::~ValueBar()
{
}

void ValueBar::init()
{
	VIEW_WIDTH = max(Theme::getRegionXDimension(renderedRegion), 670.f);
	padding = Vector2f(VIEW_WIDTH / 20, VIEW_HEIGHT / 20);
	dimensions = Vector2f(VIEW_WIDTH, (float)label.getCharacterSize() + padding.y);
	valueBar.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MainMenu/ValueBar.png"));
	valuePoint.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MainMenu/ValuePointer.png"));
}

void ValueBar::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(valueBar, states);
	target.draw(valuePoint, states);
	target.draw(label, states);
}

void ValueBar::update(int direction)
{
	if (currentValue + step * direction <= maxValue && currentValue + step * direction >= minValue)
	{
		valuePoint.setPosition(sf::Vector2f(valuePoint.getPosition().x + step * direction * 3, valuePoint.getPosition().y));
		currentValue = (float) currentValue + step * direction;
	}
}

void ValueBar::setPosition(Vector2f newPositions, Vector2f camOffset)
{
	const float VALUE_BAR_DEAD_ZONE = 30; // the x-limit of value point in value bar
	offset = newPositions;
	label.setPosition(sf::Vector2f(offset.x + camOffset.x, offset.y + camOffset.y));

	FloatRect valueBarDim = valueBar.getLocalBounds();
	valueBar.setPosition(sf::Vector2f(VIEW_WIDTH - offset.x - valueBarDim.width + camOffset.x, camOffset.y + offset.y));
	
	FloatRect valuePointDim = valuePoint.getLocalBounds();
	valuePoint.setPosition(sf::Vector2f(VIEW_WIDTH - offset.x + camOffset.x - valueBarDim.width + currentValue * 3 + VALUE_BAR_DEAD_ZONE - valuePointDim.width / 2,
		offset.y + camOffset.y + valueBarDim.height / 2 - valuePointDim.height / 2));
}

Vector2f ValueBar::getDimensions()
{
	return dimensions;
}

float ValueBar::getValue() {
	return currentValue;
}

void ValueBar::setSelected() 
{	
	label.setFillColor(Color::Red);
}

void ValueBar::unSelect()
{
	label.setFillColor(Color::White);
}
