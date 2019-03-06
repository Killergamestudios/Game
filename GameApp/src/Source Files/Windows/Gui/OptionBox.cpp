#include "pch.h"
#include "OptionBox.h"


OptionBox::OptionBox(RenderWindow *window, Text label, Font font, Theme::Regions region,
	int currentValue, vector<pair<string,string>> options)
	:GuiElement(window, label, font, region)
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
	vector <Vector2f> dimensions;
	dimensions.push_back(Vector2f(VIEW_WIDTH, (float)label.getCharacterSize() + padding.y)); 
	offset = Theme::renderRegion(renderedRegion, dimensions)[0];

	padding = Vector2f(VIEW_WIDTH / 20, VIEW_HEIGHT / 20);
	label.setPosition(Vector2f(offset.x + padding.x, offset.y + padding.y));
	selected.setString(options[(int)currentValue].first + " x " + options[(int)currentValue].second);
	selected.setCharacterSize(30);
	selected.setFont(font);
	float width = selected.getLocalBounds().width;
	selected.setPosition(Vector2f(VIEW_WIDTH - padding.x - offset.x - width, offset.y + padding.y));
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
		selected.setPosition(Vector2f(VIEW_WIDTH - padding.x - offset.x - width, offset.y + padding.y));
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