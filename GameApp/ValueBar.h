#pragma once
#include "GuiController.h"
class ValueBar : public GuiController
{
public:
	ValueBar(RenderWindow *window, Vector2f position, Text label, Font font, float currentValue, float max=100.0f, float min=0.0f, float step=10.0f);
	~ValueBar();

	void init() override;
	void draw() override;
	void update(int) override;
	void setSelected() override;
	void unSelect() override;
	float getValue() override;
	
	float maxValue;
	float minValue;
	float step;
	float currentValue;
	Sprite valueBar;
	Sprite valuePoint;
};

