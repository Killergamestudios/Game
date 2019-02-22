#include "pch.h"
#include "GuiElement.h"


GuiElement::GuiElement(RenderWindow *window, Vector2f position, Text label, Font font)
{
	m_window = window;
	offset = position;
	this->label = label;
	this->font = font;
	WIN_HEIGHT = (float)m_window->getSize().y;
	WIN_WIDTH = (float)m_window->getSize().x;
}


GuiElement::~GuiElement()
{
	
}
