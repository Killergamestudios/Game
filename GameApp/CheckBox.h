#pragma once
#include "GuiController.h"
class CheckBox : public GuiController
{
public:
	CheckBox(RenderWindow *window, Vector2f position, Text label, Font font);
	~CheckBox();
};

