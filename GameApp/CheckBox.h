#pragma once
#include "GuiElement.h"
class CheckBox : public GuiElement
{
public:
	CheckBox(RenderWindow *window, Vector2f position, Text label, Font font);
	~CheckBox();
};

