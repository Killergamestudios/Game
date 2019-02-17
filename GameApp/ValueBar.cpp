#include "pch.h"
#include "ValueBar.h"

ValueBar::ValueBar(RenderWindow *window, Vector2f position, Text label, Font font, float currentValue,
					float max, float min, float step)
	:GuiController(window,position,label,font)
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
	const float VALUE_BAR_DEAD_ZONE = 30; // the x-limit of value point in value bar
	padding = Vector2f(WIN_WIDTH/20, WIN_HEIGHT/20);
	label.setPosition(sf::Vector2f(offset.x + padding.x, offset.y + padding.y));
	valueBar.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MainMenu/ValueBar.png"));
	valuePoint.setTexture(TextureHolder::GetTexture("./graphics/interfaces/MainMenu/ValuePointer.png"));
	FloatRect valueBarDim = valueBar.getLocalBounds();
	valueBar.setPosition(sf::Vector2f(WIN_WIDTH - padding.x - offset.x - valueBarDim.width, offset.y + padding.y));
	FloatRect valuePointDim = valuePoint.getLocalBounds();
	valuePoint.setPosition(sf::Vector2f(WIN_WIDTH - padding.x - offset.x - valueBarDim.width + currentValue*3 + VALUE_BAR_DEAD_ZONE - valuePointDim.width/2,
										offset.y + padding.y + valueBarDim.height/2 - valuePointDim.height/2));
}

void ValueBar::draw()
{
	m_window->draw(valueBar);
	m_window->draw(valuePoint);
	m_window->draw(label);
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
