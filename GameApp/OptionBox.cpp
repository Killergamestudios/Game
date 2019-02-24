#include "pch.h"
#include "OptionBox.h"


OptionBox::OptionBox(RenderWindow *window, Vector2f position, Text label, Font font, int currentValue, vector<pair<string,string>> options)
	:GuiElement(window, position, label, font)
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
	padding = Vector2f(WIN_WIDTH / 20, WIN_HEIGHT / 20);
	label.setPosition(Vector2f(offset.x + padding.x, offset.y + padding.y));
	selected.setString(options[(int)currentValue].first + " x " + options[(int)currentValue].second);
	selected.setCharacterSize(30);
	selected.setFont(font);
	float width = selected.getLocalBounds().width;
	selected.setPosition(Vector2f(WIN_WIDTH - padding.x - offset.x - width, offset.y + padding.y));
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
		selected.setPosition(Vector2f(m_window->getSize().x - padding.x - offset.x - width, offset.y + padding.y));
	}
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