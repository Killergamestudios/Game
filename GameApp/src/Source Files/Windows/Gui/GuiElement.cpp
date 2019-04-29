#pragma once
#include "../../../Header Files/Windows/Gui/GuiElement.h"


GuiElement::GuiElement(RenderWindow *window, Text label, Font font, Theme* theme)
{
	m_window = window;
	this->label = label;
	this->font = font;
	VIEW_HEIGHT = (float)m_window->getView().getSize().y;
	VIEW_WIDTH = (float)m_window->getView().getSize().x;
	this->theme = theme;
	offset = Vector2f(0.0f, 0.0f);
}


GuiElement::~GuiElement()
{
	
}
