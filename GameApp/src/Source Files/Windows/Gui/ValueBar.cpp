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
	vector <Vector2f> dimensions;
	dimensions.push_back(Vector2f(VIEW_WIDTH, (float)label.getCharacterSize() + padding.y));
	offset = Theme::renderRegion(renderedRegion, dimensions)[0];

	const float VALUE_BAR_DEAD_ZONE = 30; // the x-limit of value point in value bar
	padding = Vector2f(VIEW_WIDTH/20, VIEW_HEIGHT/20);
	label.setPosition(sf::Vector2f(offset.x + padding.x, offset.y + padding.y));
	
	valueBar.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MainMenu/ValueBar.png"));
	valuePoint.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MainMenu/ValuePointer.png"));

	FloatRect valueBarDim = valueBar.getLocalBounds();
	valueBar.setPosition(sf::Vector2f(VIEW_WIDTH - padding.x - offset.x - valueBarDim.width, offset.y + padding.y));
	FloatRect valuePointDim = valuePoint.getLocalBounds();
	valuePoint.setPosition(sf::Vector2f(VIEW_WIDTH - padding.x - offset.x - valueBarDim.width + currentValue*3 + VALUE_BAR_DEAD_ZONE - valuePointDim.width/2,
										offset.y + padding.y + valueBarDim.height/2 - valuePointDim.height/2));

	

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
